namespace SuperEngineAuto.Commands

import System

public class Command:

	private parameters as ParameterGroup

	public Parameters as ParameterGroup:
		get:
			return self.parameters

	
	public abstract def Run():
		pass
		

	
	public def constructor():
		pass


