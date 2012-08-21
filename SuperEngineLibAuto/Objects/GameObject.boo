
namespace SuperEngineAuto.Objects

import System
import OpenTK
import SuperEngineAuto.Editors
import System.Collections.Generic
import System.Collections.ObjectModel

public class GameObject:

	#region Position/Orientation
	#region Events
	public class PositionChangedEventArgs(EventArgs):

		public OldPosition as Vector3:
			get:
				pass
			private set:
				pass

		public Position as Vector3:
			get:
				pass
			private set:
				pass

		public def constructor(oldPosition as Vector3, position as Vector3):
			self.OldPosition = oldPosition
			self.Position = position

	public class OrientationChangedEventArgs(EventArgs):

		public OldOrientation as Quaternion:
			get:
				pass
			private set:
				pass

		public Orientation as Quaternion:
			get:
				pass
			private set:
				pass

		public def constructor(oldOrientation as Quaternion, orientation as Quaternion):
			self.OldOrientation = oldOrientation
			self.Orientation = orientation

	
	public event PositionChanged as EventHandler[of PositionChangedEventArgs]

	public event OrientationChanged as EventHandler[of OrientationChangedEventArgs]

	
	protected virtual def OnPositionChanged(e as PositionChangedEventArgs):
		PositionChanged(self, e)

	protected virtual def OnOrientationChanged(e as OrientationChangedEventArgs):
		OrientationChanged(self, e)

	#endregion
	
	private position as Vector3

	private orientation as Quaternion

	
	public Position as Vector3:
		get:
			return position
		set:
			if position != value:
				e = PositionChangedEventArgs(position, value)
				position = value
				OnPositionChanged(e)

	public Orientation as Quaternion:
		get:
			return orientation
		set:
			if orientation != value:
				e = OrientationChangedEventArgs(orientation, value)
				orientation = value
				OnOrientationChanged(e)

	#endregion
	
	#region Parent/Child
	private children as List[of GameObject] = List[of GameObject]()

	private parent as GameObject

	
	public Children as IEnumerable[of GameObject]:
		get:
			return children
		set:
			for child as GameObject in children:
				RemoveChild(child)
			for child as GameObject in value:
				AddChild(child)

	
	public Parent as GameObject:
		get:
			return parent
		set:
			if parent != value:
				if parent:
					parent.children.Remove(self)
				parent = value
				if parent:
					parent.children.Add(self)

	
	public def AddChild(child as GameObject):
		child.Parent = self

	
	public def RemoveChild(child as GameObject):
		child.Parent = null

	#endregion
	
	#region Update/Draw
	public virtual def Update():
		pass
		

	
	public virtual def FixedUpdate():
		pass
		

	
	public virtual def Draw():
		pass
		

	#endregion
	
	#region Editor
	public virtual Editor as Type:
		get:
			return typeof(Editor)

	#endregion
	
	public def constructor(position as Vector3, orientation as Quaternion):
		self.position = position
		self.orientation = orientation


