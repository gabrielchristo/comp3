template<typename C, typename T>
void operator|(const C &list, T F)
{
	for(const auto& item : list)
		F(item);
}