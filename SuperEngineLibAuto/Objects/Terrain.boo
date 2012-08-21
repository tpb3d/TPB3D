
namespace SuperEngineAuto.Objects

import System
import OpenTK
import SuperEngineAuto.Editors

public class Terrain(GameObject):

	#region Terrain
	private width as uint

	private height as uint

	
	private heights as (single, 2)

	
	private textures as (string)

	private textureAlpha as (byte, 3)

	#endregion
	
	public def constructor():
		pass


