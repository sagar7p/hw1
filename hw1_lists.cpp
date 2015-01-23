#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head); // removes Events
double findAverage(Item* head); // Finds average from remaining
void printList(std::ostream& ofile, Item* head); //pritns to a file
void readLists(Item*& head1, Item*& head2, ifstream & input); //reads from file
void del(Item* head);

int main(int argc, char *argv[]) {
  //define the inputs and heads
  ifstream input;
  input.open(argv[1]);
  ofstream output(argv[2]);
  Item * head1 = NULL;
  Item * head2 = NULL;

  //read from file
  readLists(head1, head2, input);

  //print appropriately and call functions
  Item * head3 = concatenate(head1, head2);
  printList(output, head3);
  removeEvens(head3);
  printList(output, head3);
  double average = findAverage(head3);
  printList(output, head3);
  if(head3)
     output << average << endl;
  del(head1);
  del(head2);
  del(head3);
	return 0;
}

void del(Item * head){
   Item * next;
   if(head == NULL)
       return;
   next = head -> next;
   delete head;
   head = NULL;
   del(next);

}


//goes through the hend
Item* traverse(Item * src, Item * dest) {
   if(src == NULL)
      return dest;
   if(src -> next == NULL)
       return dest;
   dest -> next = new Item(src -> next -> val, src -> next -> next);
   src = src -> next;
   dest = dest -> next;
   traverse(src, dest);
}

//combines two lists
Item* concatenate(Item* head1, Item* head2) {
  Item * head3 = new Item(head1->val, NULL);
  Item * head4 = head3;

  head3 = traverse(head1,head3);
  head3 -> next = new Item(head2->val,NULL);
  head3 = head3 -> next;
  head3 = traverse(head2,head3);

  return head4;

}

void even(Item * current){
  if(current == NULL){
    return;
  }
  if(current -> next == NULL) {
    return;
  }
  else {
    //if the next val is zero set the next to the Item after the even value
    if(current->next->val % 2 == 0) {
        if(current -> next-> next != NULL) {
          Item * next2 = current -> next -> next;
          delete current -> next;
          current->next = next2;
        }
        else {
          delete current -> next;
          current->next = NULL;
        }
        even(current);
    }

    //skip if the value is zero
    else {
      even(current -> next);
    }
  }
}

//fnction that calls even function and checks first value
void removeEvens(Item*& head) {
  if(head -> val % 2 == 0) {
    if(head -> next != NULL) {
        Item * newhead = head -> next;
        delete head;
        head = newhead;
        removeEvens(head);
      }
    else {
      head = NULL;
      return;
    }
  }
  even(head);
}

//goes through all the values and finds the average
double average(Item * current, double sum, double length) {
    if(current == NULL) {
      return sum/length;
    }
    else {
        //continue adding to the sum and length
        sum += (current -> val);
        length++;        
        average(current->next, sum, length);
    }
}

//calls average function
double findAverage(Item* head) {
    double sum = 0.0;
    double length = 0.0;
    return average(head, sum, length);
}

//print the info to a file
void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

//read from a file
void readLists(Item*& head1, Item*& head2, ifstream & input) {

  //create a buffer to search through
  string one = "";
  string two = "";
  getline(input,one);
  istringstream first(one);
  int num;
  first >> num;
  if(!first.fail())
      head1 = new Item(num, NULL);
  Item * current = head1;
  first >> num;

  //continue to search through first string until fail
  while(!first.fail())
  {  
      Item*thing = new Item(num, NULL);
      current -> next = thing;
      current = current -> next;
      first >> num;
  }

  //get the second line and make it a linked list
  getline(input,two);
  istringstream second(two);
  int num2;
  second >> num2;
  if(!second.fail())
      head2 = new Item(num2, NULL);
  current = head2;
  second >> num2;

  //search through the buffer for numbers until fail
  while(!second.fail()) {  
      Item*thing = new Item(num2, NULL);
      current -> next = thing;
      current = current -> next;
      second >> num2;
  }

}

