
namespace SuperEngineAuto.Maths

import System
import OpenTK
import System.Collections.Generic

public struct Spline:

	public struct Segment:
		pass

	
	private nodes as List[of Vector4]

	private points as List[of Vector4]

	private segments as List[of Segment]

	private length as single

	private continuous as bool

	
	public Nodes as IEnumerable[of Vector4]:
		get:
			return nodes.AsReadOnly()
		set:
			nodes = List[of Vector4](value)
			CalcSpline()

	
	public Segments as IEnumerable[of Segment]:
		get:
			return segments.AsReadOnly()

	
	public Length as single:
		get:
			return length

	
	public Continuous as bool:
		get:
			return continuous
		set:
			if continuous != value:
				continuous = value
				CalcSpline()

	
	public def CalcSpline():
		tmpLen as single = 0.0F
		count as int = nodes.Count
		if count < 2:
			return
		if continuous:
			points.Add(nodes[(count - 1)])
			points.AddRange(nodes)
			points.Add(nodes[0])
		else:
			diff as Vector4
			diff = (nodes[0] + (nodes[1] - nodes[0]))
			points.Add(diff)
			points.AddRange(nodes)
			diff = (nodes[(count - 2)] - nodes[(count - 1)])
			diff = (nodes[(count - 1)] + diff)
			points.Add(diff)
		for i in range(1, (count - 2)):
			tmp = Segment(points[(i - 1)], points[i], points[(i + 1)], points[(i + 2)])
			segments.Add(tmp)
			tmp.StartDistance = tmpLen
			tmpLen += tmp.Length
		length = tmpLen

	
	public def Point(distance as single) as Vector4:
		tmp as Segment = segments.Find({ s | return ((s.StartDistance <= distance) and ((s.StartDistance + s.Length) >= distance)) })
		u as single = ((distance - tmp.StartDistance) / tmp.Length)
		return tmp.Point(u)

	
	public def constructor():
		pass

	
	public def constructor(n as IEnumerable[of Vector4]):
		Nodes = n


