#ifndef __JINX_TYPE_H_
#define __JINX_TYPE_H__

#include <unordered_map>

/**
 * TypeMap container that holds values of ValueType in an
 * unordered map, indexed generated static IDs.
 */
template <class ValueType>
class TypeMap {
	typedef std::unordered_map<int, std::unique_ptr<ValueType>> InternalTypeMap;

public:
	typedef typename InternalTypeMap::iterator iterator;
	typedef typename InternalTypeMap::const_iterator const_iterator;
	typedef typename InternalTypeMap::value_type value_type;

	const_iterator begin() const { return m_map.begin(); }
	const_iterator end() const { return m_map.end(); }
	iterator begin() { return m_map.begin(); }
	iterator end() { return m_map.end(); }

	template <class Key>
	iterator find() {
		return m_map.find(getTypeId<Key>());
	};

	template <class Key>
	void registerType(std::unique_ptr<ValueType> &&value) {
		m_map[getTypeId<Key>()] = std::move(value);
	};
private:
	template <class Key>
	inline static int getTypeId() {
		static const int id = LastTypeId++;
		return id;
	}

	static int LastTypeId;
	InternalTypeMap m_map;
};

template <class ValueType>
int TypeMap<ValueType>::LastTypeId(0);

#endif