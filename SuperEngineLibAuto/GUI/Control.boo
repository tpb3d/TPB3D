
namespace SuperEngineAuto.GUI

import System
import OpenTK
import OpenTK.Input

public class Control:

	#region Positioning
	private x as int

	private y as int

	private width as int

	private height as int

	public X as int:
		get:
			return self.x
		set:
			x = value

	
	public Y as int:
		get:
			return self.y
		set:
			y = value

	
	public Width as int:
		get:
			return self.width
		set:
			width = value

	
	public Height as int:
		get:
			return self.height
		set:
			height = value

	#endregion
	
	private focused as bool

	
	public virtual def OnMouseDown(e as MouseEventArgs):
		pass
		

	
	public virtual def OnMouseUp(e as MouseEventArgs):
		pass
		

	
	public virtual def OnKeyDown(e as KeyboardKeyEventArgs):
		pass
		

	
	public virtual def OnKeyUp(e as KeyboardKeyEventArgs):
		pass
		

	
	public virtual def Draw():
		pass
		

	
	public def constructor():
		pass


