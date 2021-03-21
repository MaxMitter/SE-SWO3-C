template <typename T>
list_node<T>::list_node(value_type value)
	: m_value{value}
	, m_next{ nullptr }
	{ }

template <typename T>
list_node<T>::list_node(value_type value, list_node* next)
	: m_value{ value }
	, m_next{ next }
	{ }


template <typename T>
list_node<T>::~list_node() {
	delete m_value;
}