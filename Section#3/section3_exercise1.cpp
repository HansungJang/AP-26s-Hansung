 #include<iostream>
 #include<string>
 #include<vector> 
 #include<sstream>

 using namespace std; 

 typedef struct node

{
    int item_id;
    string item_descr; 
    struct node* next;
} Item;

Item* inventory = nullptr; // (global) pointer to the first item in list
// last node 만들기 


/* function declarations: */
void add_item(int id, string descr); // function to add new item
void remove_item(int id);            // removal function
void print_inventory();              // display all contents of inventory
void delete_all(); 

/* code segment maybe to be placed in main() function: */
int main() 
{
	int selection;
	Item header = {-1, "header", nullptr}; 
	inventory = &header; 
	//  header item 만들어야지 
	while (true)
	{
		cout << "Current inventory:"<<endl;
		print_inventory();
		cout << "#Menu : " << endl;
		cout << "Add New : (insert : 0)" << endl;
		cout << "Delete : (insert : 1) " << endl;
		cout << "Print : (insert : 2)" << endl;
		cout << "End : (insert : 3)" << endl;
		cout << "Select : " ; 

		cin >> selection;
		switch(selection)
		{
			case 0 : 
				{		
					// query name, generate id and call add_item()
					cout << "Insert ID, description [Id, Describe]: "; 
					string input; 
					cin.ignore();
					getline(cin, input); 

					stringstream parser(input);
					string id_text;
					string description;
					getline(parser, id_text, ',');
					getline(parser, description);
					add_item(stoi(id_text), description);			
					break; 
				}
			case 1 : 
				{
					cout << "Insert Delete ID : "; 
					int id; 
					// getline(cin, id); 
					// remove_item(stoi(id)); 
					cin >> id; 
					remove_item(id); 
					break; 
				}
			case 2 : 
				{
					print_inventory();
					break; 
				}
			
			delete_all(); 
			break; 
		}
		if(selection >= 3) break; 
	}
	// NOTE: free all memory allocations before exiting program!

	return 0; 
}

void add_item(int id, string descr) // function to add new item
{
	// 1. 새로운 item만들고
	Item* newItem = new Item();
	Item* current = inventory;

	// 2. 입력값 넣기
	newItem->item_id = id;
	newItem->item_descr = descr;
	newItem->next = nullptr;

	// last node쓰면 O(1)으로 끝낼 수 있음
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = newItem;
}

void remove_item(int id)            // removal function
{
	Item* curr = inventory;
	Item* next = inventory->next; 

	while(1)
	{
		if(curr == nullptr) break; 
		if(next->item_id  == id)
		{
			curr->next = next->next; 
			delete next; 
			break; 

		}		
		curr = next; 
		next = next->next; 
	}
}

void print_inventory()              // display all contents of inventory
{
	Item* handle = inventory; 

	cout << endl; 

	while(handle != nullptr && inventory->next != nullptr)
	{
		if(handle->item_id > 0 && handle->item_descr != "header")
		{
			cout << "item id : "<< handle->item_id << " " << "item desc: " << handle->item_descr << endl;	
		}  
		 
		handle = handle->next;  
	}
	cout << endl; 
}

void delete_all()
{
	Item* handle = inventory; 
 	while(handle->next != nullptr)
	{
		remove_item(handle->next->item_id); 
	}
	delete handle; 
}