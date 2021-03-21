//#pragma once
//
//#include <ml5/ml5.h>
//
//template <typename T>
//class list_node : public ml5::object<T>, MI5_DERIVE(list_node<T>, ml5::object) {
//	MI5_INJECT(list_node<T>)
//	using const_reference = T const&;
//	using reference = T&;
//	using size_type = std::size_t;
//	using value_type = T;
//
//	public:
//		list_node(value_type value);
//		list_node(value_type value, list_node* next);
//
//		explicit list_node(const value_type& value)
//			: m_value{value}
//		, m_next{ nullptr } {};
//
//	
//		~list_node();
//
//	private:
//		value_type* m_value{ nullptr };
//		list_node* m_next{ nullptr };
//};
//
//#include "list_node.inl"