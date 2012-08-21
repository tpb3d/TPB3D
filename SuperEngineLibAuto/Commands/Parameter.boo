namespace SuperEngineAuto.Commands

import System

public class Parameter:

	public Name as string:
		get:
			pass
		private set:
			pass

	public Locked as bool:
		get:
			pass
		private set:
			pass

	private val as object

	public Value as object:
		get:
			return val
		set:
			if ValueType.IsAssignableFrom(value.GetType()) and (not ((value isa ParameterGroup) and Locked)):
				val = value
			else:
				raise InvalidCastException()

	public ValueType as Type:
		get:
			pass
		private set:
			pass

	public def constructor(name as string, val as object, type as Type):
		self.Name = name
		self.Value = val
		self.ValueType = type
		self.Locked = false

	public def constructor(name as string, val as object, type as Type, locked as bool):
		self(name, val, type)
		self.Locked = locked

	public def Lock():
		Locked = true

	internal def Unlock():
		Locked = false


