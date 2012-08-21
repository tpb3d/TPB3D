namespace SuperEngine

import System
import Boo.Lang
import Boo.Lang.Useful
import Boo.Lang.Extensions as BooExtensions

class PropertyChangedEventHandler[of T]:
"""Description of PropertyChangedEventHandler"""
	
	[BooExtensions.Property(Old as T, ProtectedSetter: true)]
	private _old
	
	[BooExtensions.Property(New as T, ProtectedSetter: true)]
	private _new
	
	public def constructor():
		pass

