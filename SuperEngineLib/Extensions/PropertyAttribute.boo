namespace SuperEngine.Extensions

import System
import Boo.Lang
import Boo.Lang.Useful
import Boo.Lang.Extensions as BooExtensions
import Boo.Lang.Compiler.Ast
import SuperEngine

class PropertyAttribute(Boo.Lang.Compiler.AbstractAstAttribute):
"""Description of PropertyAttribute"""

	protected _propertyName as ReferenceExpression

	protected _propertyType as TypeReference

	protected _setPreCondition as Expression
	
	protected _protected as BoolLiteralExpression

	protected _protectedSetter as BoolLiteralExpression

	protected _observable as BoolLiteralExpression
	
	protected _attributes as ListLiteralExpression

	public def constructor(propertyName as ReferenceExpression):
		self(propertyName, null)

	public def constructor(propertyNameAndType as TryCastExpression):
		re = propertyNameAndType.Target as ReferenceExpression
		if not re:
			raise ArgumentException('Left-side must be a ReferenceExpression (ie. name of the property)', 'propertyNameAndType')
		_propertyType = propertyNameAndType.Type
		self(re, null)

	public def constructor(propertyName as ReferenceExpression, setPreCondition as Expression):
		if propertyName is null:
			raise ArgumentNullException('propertyName')
		_propertyName = propertyName
		_setPreCondition = setPreCondition

	public def constructor(propertyNameAndType as TryCastExpression, setPreCondition as Expression):
		re = propertyNameAndType.Target as ReferenceExpression
		if not re:
			raise ArgumentException('Left-side must be a ReferenceExpression (ie. name of the property)', 'propertyNameAndType')
		_propertyType = propertyNameAndType.Type
		self(re, setPreCondition)

	virtual HasSetter as bool:
		get:
			return true

	Protected:
		get:
			return _protected
		set:
			_protected = value

	ProtectedSetter:
		get:
			return _protectedSetter
		set:
			if not HasSetter:
				raise ArgumentException("ProtectedSetter", "ProtectedSetter can not be set on a getter.")
			_protectedSetter = value

	protected IsProtected:
		get:
			if _protected is null:
				return false
			return _protected.Value

	protected IsProtectedSetter:
		get:
			if _protectedSetter is null:
				return false
			return _protectedSetter.Value

	Observable:
		get:
			return _observable
		set:
			_observable = value
	
	protected IsObservable:
		get:
			if _observable is null:
				return false
			return _observable.Value
	
	protected ChangedEventName:
		get:
			return (_propertyName.Name + 'Changed')
	
	Attributes:
		get:
			return _attributes
		set:
			_attributes = value
	
	public override def Apply(node as Node):
		f = (node as Field)
		if f is null:
			InvalidNodeForAttribute('Field')
			return 
		
		p = Property()
		if f.IsStatic:
			p.Modifiers |= TypeMemberModifiers.Static
		if IsProtected:
			p.Modifiers |= TypeMemberModifiers.Protected
		else:
			p.Modifiers |= TypeMemberModifiers.Public
		p.Name = _propertyName.Name
		if not _propertyType:
			p.Type = f.Type
		else:
			p.Type = _propertyType
		p.Getter = CreateGetter(f)
		p.Setter = CreateSetter(f)
		p.LexicalInfo = LexicalInfo
		
		if (Attributes is not null) and (Attributes.Items.Count > 0):
			for item as Expression in Attributes.Items:
				p.Attributes.Add(ConvertExpressionToAttribute(item))
		
		f.DeclaringType.Members.Add(p)
		
		if IsObservable:
			f.DeclaringType.Members.Add(CreateChangedEvent(f))
	
	public static def ConvertExpressionToAttribute(item as Expression) as Boo.Lang.Compiler.Ast.Attribute:
		att as Boo.Lang.Compiler.Ast.Attribute = Boo.Lang.Compiler.Ast.Attribute(item.LexicalInfo)
		if item isa MethodInvocationExpression:
			m = cast(MethodInvocationExpression, item)
			att.Name = m.Target.ToString()
			att.Arguments = m.Arguments
			att.NamedArguments = m.NamedArguments
		else:
			att.Name = item.ToString()
		return att

	
	protected virtual def CreateGetter(f as Field) as Method:
		// get:
		//		return <f.Name>
		getter = Method()
		getter.Name = 'get'
		getter.Body.Statements.Add(ReturnStatement(super.LexicalInfo, ReferenceExpression(f.Name), null))
		return getter

	
	protected virtual def CreateSetter(f as Field) as Method:
		setter = Method()
		setter.Name = 'set'

		if IsProtectedSetter:
			setter.Visibility = TypeMemberModifiers.Protected

		if _setPreCondition is not null:
			setter.Body.Add(RaiseStatement(_setPreCondition.LexicalInfo, AstUtil.CreateMethodInvocationExpression(AstUtil.CreateReferenceExpression('System.ArgumentException'), StringLiteralExpression((('precondition \'' + _setPreCondition.ToString()) + '\' failed:'))), StatementModifier(StatementModifierType.Unless, _setPreCondition)))
		tmp = Block()
		tmp.Add(BinaryExpression(super.LexicalInfo, BinaryOperatorType.Assign, MemberReferenceExpression(CreateRefTarget(f), f.Name), ReferenceExpression('value')))
		
		if IsObservable:
			setter.Locals.Add(Local(Declaration('oldValue', f.Type)))
			tmp.Add(BinaryExpression(super.LexicalInfo, BinaryOperatorType.Assign, ReferenceExpression('oldValue'), MemberReferenceExpression(CreateRefTarget(f), f.Name)))
			tmp.Add(BinaryExpression(super.LexicalInfo, BinaryOperatorType.Assign, MemberReferenceExpression(CreateRefTarget(f), f.Name), ReferenceExpression('value')))
			mie = MethodInvocationExpression(ReferenceExpression(ChangedEventName))
			mie.Arguments.Add(SelfLiteralExpression())
			mie.Arguments.Add(MemberReferenceExpression(MemberReferenceExpression(ReferenceExpression('System'), 'EventArgs'), 'Empty'))
			tmp.Add(mie)
		else:
			tmp.Add(BinaryExpression(super.LexicalInfo, BinaryOperatorType.Assign, MemberReferenceExpression(CreateRefTarget(f), f.Name), ReferenceExpression('value')))
		
		setter.Body.Add(IfStatement(BinaryExpression(super.LexicalInfo, BinaryOperatorType.NotMatch, ReferenceExpression('value'), MemberReferenceExpression(CreateRefTarget(f), f.Name)), tmp, Block()))
		return setter

	
	private def CreateRefTarget(f as Field) as Expression:
		if f.IsStatic:
			return ReferenceExpression(LexicalInfo, f.DeclaringType.Name)
		return SelfLiteralExpression(LexicalInfo)

	protected def CreateChangedEvent(f as Field) as Event:
		e = Event(_observable.LexicalInfo)
		e.Name = ChangedEventName
		tag = CodeBuilder.TypeSystemServices.Map(typeof(PropertyChangedEventHandler))
		eventType = GenericTypeReference(f.LexicalInfo, tag.FullName)
		eventType.Entity = tag
		eventType.GenericArguments = TypeReferenceCollection()
		if not _propertyType:
			eventType.GenericArguments.Add(f.Type)
		else:
			eventType.GenericArguments.Add(_propertyType)
		e.Type = eventType
		if IsProtected or IsProtectedSetter:
			e.Visibility = TypeMemberModifiers.Protected
		else:
			e.Visibility = TypeMemberModifiers.Public
		return e
