
namespace SuperEngineAuto.Objects

import System
import OpenTK
import SuperEngineAuto.Editors
import System.Collections.Generic

public class Spline(MeshObject):

	public final class SplineNode(GameObject):

		private roll as single

		
		public Roll as single:
			get:
				return roll
			set:
				if roll != value:
					roll = value

		
		public def constructor(vec as Vector4):
			Position = vec.Xyz
			Roll = vec.W
		

	
	private next as Spline

	private prev as Spline

	
	public Next as Spline:
		get:
			return next
		set:
			if next != value:
				next = value
				if next:
					next_start = next.Start
				else:
					tmp as Vector4 = (end + (end - start))
					next_start = SplineNode(tmp)

	
	public Prev as Spline:
		get:
			return prev
		set:
			if prev != value:
				prev = value
				if prev:
					prev_end = prev.End
					if start and end:
						Prev.Next = self
				elif start and end:
					tmp as Vector4 = (start + (start - end))
					prev_end = SplineNode(tmp)

	
	private prev_end as SplineNode

	private start as SplineNode

	private end as SplineNode

	private next_start as SplineNode

	
	private length as single

	
	public Length as single:
		get:
			return length

	
	public def constructor(_start as SplineNode, _end as SplineNode, _next as Spline, _prev as Spline):
		if not _start:
			raise ArgumentNullException('_start')
		if not _end:
			raise ArgumentNullException('_end')
		Start = _start
		End = _end
		Next = _next
		Prev = _prev
		length = CalcLength()

	
	public def CalcLength() as single:
		return CalcLength(((P1 - P2).Length / 100))

	
	public def CalcLength(len as single) as single:
		return CalcLength(0, 1, len)

	
	public def CalcLength(u0 as single, u1 as single, len as single) as single:
		return CalcLength(u0, u1, (len * len), 2)

	
	public def CalcLength(u0 as single, u1 as single, len as single, maxDepth as int) as single:
		return CalcLength(u0, u1, (len * len), maxDepth, 0)

	
	private def CalcLength(u0 as single, u1 as single, lenSquared as single, maxDepth as int, depth as int) as single:
		umid as single = ((u0 + u1) / 2)
		P0 as Vector3 = Point(u0)
		P1 as Vector3 = Point(u1)
		if ((P0 - P1).LengthSquared > lenSquared) or (depth < maxDepth):
			len0 as single = CalcLength(u0, umid, lenSquared, maxDepth, (depth + 1))
			len1 as single = CalcLength(umid, u1, lenSquared, maxDepth, (depth + 1))
			return (len0 + len1)
		else:
			return (P0 - P1).Length

	
	public def Point(s as single) as Vector4:
		h1 as single = (((2 * Math.Pow(s, 3)) - (3 * Math.Pow(s, 2))) + 1)
		h2 as single = (((-2) * Math.Pow(s, 3)) + (3 * Math.Pow(s, 2)))
		h3 as single = ((Math.Pow(s, 3) - (2 * Math.Pow(s, 2))) + s)
		h4 as single = (Math.Pow(s, 3) - Math.Pow(s, 2))
		p as Vector4 = ((((h1 * start) + (h2 * end)) + (h3 * (0.5 * (end - prev_end)))) + (h4 * (0.5 * (next_start - start))))
		return p

	
	public def constructor():
		pass


