namespace SuperEngineAuto.Commands

import System
import System.Collections.Generic

public final class ParameterGroup:

	public Locked as bool:
		get:
			pass
		private set:
			pass

	
	private parameters as Dictionary[of string, Parameter]

	public Parameters as ReadOnlyDictionary[of string, Parameter]:
		get:
			return ReadOnlyDictionary[of string, Parameter](self.parameters)

	
	public def constructor(parameterGroup as ParameterGroup):
		self.parameters = Dictionary[of string, Parameter](parameterGroup.parameters)
		Locked = false

	
	public def constructor(parameters as Dictionary[of string, Parameter]):
		self.parameters = parameters
		Locked = false

	
	private def constructor():
		self.parameters = Dictionary[of string, Parameter]()
		Locked = false

	
	public def Lock():
		Locked = true

	private def Unlock():
		Locked = false

	public def Lock(name as string):
		parameters[name].Lock()

	public def Unlock(name as string):
		parameters[name].Unlock()
	
	public self[name as string]:
		get:
			return parameters[name].Value
		set:
			parameters[name].Value = value
	
	#region Add()
	private def Add(param as Parameter):
		if Locked:
			raise AccessViolationException('ParameterGroup is Locked')
		else:
			parameters.Add(param.Name, param)

	public def Add(name as string, val as object):
		Add(Parameter(name, val, val.GetType()))

	public def Add(name as string, val as object, type as Type):
		Add(Parameter(name, val, type))

	public def Add(name as string, val as ParameterGroup):
		Add(Parameter(name, val, typeof(ParameterGroup)))

	public def Add(name as string, val as ParameterGroup, locked as bool):
		Add(Parameter(name, val, typeof(ParameterGroup), locked))

	#endregion
	
	private static terrainBrush as ParameterGroup

	public static TerrainBrush as ParameterGroup:
		get:
			if not terrainBrush:
				terrainBrush as ParameterGroup = ParameterGroup()
				terrainBrush.Add('radius', 10)
				terrainBrush.Add('sensitivity', 10)
				terrainBrush.Add('falloff', 10)
				terrainBrush.Lock()
			return terrainBrush

	
	private static terrainTextureBrush as ParameterGroup

	public static TerrainTextureBrush as ParameterGroup:
		get:
			if not terrainTextureBrush:
				terrainTextureBrush as ParameterGroup = ParameterGroup(TerrainBrush)
				terrainTextureBrush.Add('texture', '(none)')
				//terrainTextureBrush.Add("scale", 1.0f);
				//terrainTextureBrush.Add("rotation", 0);
				terrainTextureBrush.Lock()
			return terrainTextureBrush


