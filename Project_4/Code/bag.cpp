#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

template <typename ItemType>
Bag<ItemType>::~Bag()
{
	link_list *tmp = content;
	content = content -> next;
	delete tmp;
	for(int i=0; i<my_size; i++) //delete all data in linked_list
	{
		tmp = content;
		content = content -> next;
		delete tmp;
	}
	cout<<"Bag has been destructed.\n";
}

template <typename ItemType>
Bag<ItemType>::Bag()
{
	content = new link_list;
	content->previous = content;
	content->next = content;
	my_size = 0;
	my_uniquesize = 0;
	need_init = true;
	iterator = NULL;
	cout<<"Bag has been constructed.\n";
}

template <typename ItemType>
Bag<ItemType>::Bag(Bag<ItemType> &target)
{
	my_size = target.size();
	my_uniquesize = target.uniqueSize();
	need_init = true;
	iterator = NULL;
	
	content = new link_list;
	target.start();
	link_list *tmp = content;    
	      
	for(int i=0; i<target.size(); i++) //load every data in target to Bag
	{
		tmp -> next = new link_list;
		tmp -> next->data = target.currentValue();
		tmp -> next -> previous = tmp;
		tmp = tmp -> next;
		target.next();
	}
	
	tmp -> next = content;     //let the last node point to first node(dummy node)
	content -> previous = tmp; //let the  first node(dummy node) point to last node 
	
	cout<<"Bag copy has been constructed.\n";
}

template <typename ItemType>
void Bag<ItemType>::operator=(Bag<ItemType> &target)
{
	//clean original data in Bag except the dummy node
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) 
	{
			link_list *out = tmp;
			tmp = tmp->next;
			delete out;			
	}
	
	my_size = target.size();
	my_uniquesize = target.uniqueSize();
	iterator = NULL;
	need_init = true;
	
	tmp = content;
	target.start();
	for(int i=0; i<target.size(); i++) //load every data in target to Bag
	{
		tmp -> next = new link_list;
		tmp -> next->data = target.currentValue();
		tmp -> next -> previous = tmp;
		tmp = tmp -> next;
		target.next();
	}
	
	tmp -> next = content;     //let the last node point to first node(dummy node)
	content -> previous = tmp; //let the  first node(dummy node) point to last node 
	
	cout<<"Bag assignment operator\n";
}

template <typename ItemType>
bool Bag<ItemType>::empty() const
{
	return my_size == 0;
}

template <typename ItemType>
int Bag<ItemType>::size() const
{
	return my_size;
}

template <typename ItemType>
int Bag<ItemType>::uniqueSize() const
{
	return my_uniquesize;
}

template <typename ItemType>
bool Bag<ItemType>::insert(const ItemType& value)
{
	need_init = true;
	
	bool uni = true;
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) //check if exist data in Bag which equal to value
	{
		if(tmp -> data == value) // find data  which equal to value, let uni be false
		{
			uni = false;
			break;
		}
		else tmp = tmp->next;
	}
	if(uni) my_uniquesize++;
	
	link_list *last = content->previous, *now = new link_list;
	now -> data = value;
	now -> previous = last;
	now -> next = content;
	content -> previous = now;
	last -> next = now;
	
	my_size++;
	return true;
}

template <typename ItemType>
int Bag<ItemType>::erase(const ItemType& value)
{
	need_init = true;
	
	int retval = 0;
	bool uni = true; //true : the number of   data which equal to value   is <= 1, false : oppsite
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) //erase the data which equal to value
	{
		if(tmp -> data == value && retval == 0)
		{
			link_list *out = tmp;
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;
			tmp = tmp->next;
			delete out;
			retval++;
		}
		else if(tmp -> data == value) 
		{
			uni = false;    // exist another data equal to value, so let uni be false
			break;
		}
		else tmp = tmp->next;
	}
	my_size = my_size - retval;
	if(uni && retval == 1) 
		my_uniquesize--; // if erase a data, and it's an unique data.
	return 
		retval;
}

template <typename ItemType>
int Bag<ItemType>::eraseAll(const ItemType& value)
{
	need_init = true;
	
	int retval = 0;
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) //erase all data which equal to value
	{
		if(tmp -> data == value)
		{
			link_list *out = tmp;
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;
			tmp = tmp->next;
			delete out;
			retval++;
		}
		else tmp = tmp->next;
	}
	my_size = my_size - retval;
	if(retval > 0 ) 
		my_uniquesize--; // if really erase some data, my_uniquesize minus 1
	return 
		retval;
}

template <typename ItemType>
bool Bag<ItemType>::contains(const ItemType& value) const
{
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) 
	{
		if(tmp -> data == value)
		{
			return true;
		}
		else tmp = tmp->next;
	}
	return false;
}

template <typename ItemType>
int Bag<ItemType>::count(const ItemType& value) const
{
	int retval = 0;
	link_list *tmp = content -> next;
	for(int i=0; i<my_size; i++) 
	{
		if(tmp -> data == value)
		{
			retval++;
		}
		tmp = tmp->next;
	}
	return retval;
}

template <typename ItemType>
void Bag<ItemType>::start()
{
	if(my_size == 0)
	{
		cout<<"Please input item\n";
		return;
	}
	need_init = false;
	iterator = content->next;
	current_count = 1;
}

template <typename ItemType>
void Bag<ItemType>::next()
{
	if(need_init)
	{
		cout<<"Please initializes\n";
		return;
	}
	if(current_count >= my_size)
	{
		iterator = NULL;
		current_count = 0;
		return;
	}
	else if(iterator != NULL)
	{
		iterator = iterator -> next;
		current_count ++;
		return;
	}
	else
	{
		//cout<<"ended!!!\n";
		return;
	}
}

template <typename ItemType>
bool Bag<ItemType>::ended() const
{
	return iterator == NULL;
}

template <typename ItemType>
const ItemType& Bag<ItemType>::currentValue() const
{
	if(need_init)
	{
		cout<<"Please initializes\n";
		return content->data;
	}
	if(iterator == NULL)
	{
		//cout<<"ended!!!\n";
		return content->data;
	}
	return iterator->data;
}

template <typename ItemType>
int Bag<ItemType>::currentCount() const
{
	return current_count;
}

template <typename ItemType>
void combine(Bag<ItemType>& bag1, Bag<ItemType>& bag2, Bag<ItemType>& result)
{
	Bag<ItemType> data_bag1(bag1), data_bag2 ( bag2);
	
	if(result.size() > 0)
	{
		result.start(); //erase all data in result
		while(1)
		{
			ItemType tmp = result.currentValue();
			result.eraseAll(tmp);
			if(result.size() > 0) 
				result.start();
			else 
				break;
		}
	}
	
	data_bag1.start();
	for(int i=0; i<data_bag1.size(); i++) // insert every data in bag1 to result
	{
		result.insert(data_bag1.currentValue());
		data_bag1.next();
	}
	
	data_bag2.start();
	for(int i=0; i<data_bag2.size(); i++) // insert every data in bag2 tp result
	{
		result.insert(data_bag2.currentValue());
		data_bag2.next();
	}
	return;
}


template <typename ItemType>
void subtract(Bag<ItemType>& bag1, Bag<ItemType>& bag2, Bag<ItemType>& result)
{
	Bag<ItemType> data_bag1(bag1), data_bag2 ( bag2);
	
	if(result.size() > 0) //erase all data in result
	{
		result.start();
		while(1)
		{
			ItemType tmp = result.currentValue();
			result.eraseAll(tmp);
			if(result.size() > 0) 
				result.start();
			else 
				break;
		}
	}

	if(data_bag1.size() > 0)
	{
		int num1, num2;
		data_bag1.start();
		while(1)
		{
			num1 = data_bag1.count(data_bag1.currentValue());
			num2 = data_bag2.count(data_bag1.currentValue());
			if(num1 > num2)
			{
				for(int i=0; i < num1 - num2; i++) // if num1 > num2, insert (num1 - num2) data into result
				{
					result.insert(data_bag1.currentValue());
				}
			}
			ItemType tmp = data_bag1.currentValue();

			data_bag1.eraseAll(tmp); //after insert, erase all of such data
			
			if(data_bag1.size() > 0)  
				data_bag1.start();
			else 
				break;
		}
	}
}
