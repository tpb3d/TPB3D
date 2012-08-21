namespace System.Collections.Generic
import System


class ReadOnlyDictionary[of TKey, TValue](IDictionary[of TKey, TValue]):
	private _dictionary as IDictionary[of TKey, TValue]
	
	
	public def constructor():
		_dictionary = Dictionary[of TKey, TValue]()
	
	
	public def constructor(dictionary as IDictionary[of TKey, TValue]):
		_dictionary = dictionary
	
	
	#region IDictionary[of TKey,TValue] Members
	
	public def Add(key as TKey, value as TValue):
		raise NotSupportedException('This dictionary is read-only')
	
	
	public def ContainsKey(key as TKey) as bool:
		return _dictionary.ContainsKey(key)

	
	public Keys as ICollection[of TKey]:
		get:
			return _dictionary.Keys
	
	
	public def Remove(key as TKey) as bool:
		raise NotSupportedException('This dictionary is read-only')
	
	
	public def TryGetValue(key as TKey, ref value as TValue) as bool:
		return _dictionary.TryGetValue(key, value)
	
	
	public Values as ICollection[of TValue]:
		get:
			return _dictionary.Values
	
	
	public self[key as TKey] as TValue:
		get:
			return _dictionary[key]
		set:
			raise NotSupportedException('This dictionary is read-only')

	
	#endregion
	
	#region ICollection[of KeyValuePair[of TKey,TValue]] Members
	
	public def Add(item as KeyValuePair[of TKey, TValue]):
		raise NotSupportedException('This dictionary is read-only')

	
	public def Clear():
		raise NotSupportedException('This dictionary is read-only')

	
	public def Contains(item as KeyValuePair[of TKey, TValue]) as bool:
		return _dictionary.Contains(item)

	
	public def CopyTo(array as (KeyValuePair[of TKey, TValue]), arrayIndex as int):
		_dictionary.CopyTo(array, arrayIndex)

	
	public Count as int:
		get:
			return _dictionary.Count

	
	public IsReadOnly as bool:
		get:
			return true

	
	public def Remove(item as KeyValuePair[of TKey, TValue]) as bool:
		raise NotSupportedException('This dictionary is read-only')

	
	#endregion
	
	#region IEnumerableof KeyValuePair[of TKey,TValue]] Members
	
	public def GetEnumerator() as IEnumerator[of KeyValuePair[of TKey, TValue]]:
		return _dictionary.GetEnumerator()

	
	#endregion
	
	#region IEnumerable Members
	
	def System.Collections.IEnumerable.GetEnumerator() as System.Collections.IEnumerator:
		return (_dictionary as System.Collections.IEnumerable).GetEnumerator()
	
	#endregion


