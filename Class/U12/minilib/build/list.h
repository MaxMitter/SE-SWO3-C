//#pragma once
//
//#include "list_node.h"
//
//template <typename T>
//class list : ml5::container,
//	MI5_DERIVE(list<T>, ml5::container<T>) {
//	MI5_INJECT(list<T>)
//
//	public:
//
//		~list() {
//			
//		}
//	
//		void add(T value);
//		void clear() ;
//		bool contains(T const& value) const noexcept { return false; }
//		void remove(T const& value) {
//			
//		}
//		std::size_t size() const noexcept {
//			return m_size;
//		}
//
//		std::unique_ptr<ml5::iterator<T>> make_iterator() {
//			return nullptr;
//		}
//	private:
//		list_node<T>* m_head{ nullptr };
//		list_node<T>* m_tail{ nullptr };
//		std::size_t m_size{ 0 };
//};