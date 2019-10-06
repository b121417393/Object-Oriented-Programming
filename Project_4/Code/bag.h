template <typename ItemType>

class Bag {
	public:
		Bag();  // create an empty bag.
		Bag(Bag &target);
		void operator=(Bag &target);
		bool empty() const;	// return true iff the bag is empty.
		int size() const;	// return the number of items in the bag.
		int uniqueSize() const;	// return the number of distinct items in the bag.
		bool insert(const ItemType& value);	// insert value into the bag. Return true iff the value could be inserted.

		int erase(const ItemType& value);
		// remove one instance of value from the bag if present. Return the number of instances removed, which will be 1 or 0.

		int eraseAll(const ItemType& value);
		// remove all instances of value from the bag if present. Return the number of instances removed.

		bool contains(const ItemType& value) const;	// return true iff value is in the bag.
		int count(const ItemType& value) const;	// return the number of instances of value in the bag.
		void start();
		void next();
		bool ended() const;
		const ItemType& currentValue() const;
		int currentCount() const;
		
		~Bag();
		
		struct link_list{
			ItemType data;
			link_list *previous, *next;
		};
		
	private:
		bool need_init; //1 : need to call start(), 0: don't need to call
		link_list *content; //point to the first node(dummy node) in list
		int my_size, my_uniquesize, current_count;
		link_list *iterator;	
};

template <typename ItemType >
void combine(Bag<ItemType>& bag1, Bag<ItemType>& bag2, Bag<ItemType>& result);

template <typename ItemType >
void subtract(Bag<ItemType>& bag1, Bag<ItemType>& bag2, Bag<ItemType>& result);

#include "bag.cpp"
