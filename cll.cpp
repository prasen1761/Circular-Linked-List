#include<iostream>
#include<limits>

using namespace std;

int INF=std::numeric_limits<int>::max();

struct Node
{
  int data;
  struct Node * next;
};

struct Node * root=NULL;
int total=0;

struct Node * createNode(int value)
{
  struct Node * np=(struct Node *)malloc(sizeof(struct Node));
  np->data=value;
  np->next=NULL;
  return np;
}

struct Node * addToFront(struct Node * nptr)
{
	if(root==NULL)
	{
		root=nptr;
		nptr->next=nptr;
		total++;
		cout<<"First Node added."<<endl;
		return root;
	}
	else
	{
		struct Node * ptr_last=root;
		while(ptr_last->next!=root)
		{
			ptr_last=ptr_last->next;
		}
		struct Node * prev_root=root;
		root=nptr;
		nptr->next=prev_root;
		ptr_last->next=root;
		total++;
		cout<<"Node added to Front."<<endl;
		return root;
    }
}

struct Node * addToEnd(struct Node * nptr)
{
	struct Node * ptr_last=root;
	while(ptr_last->next!=root)
	{
		ptr_last=ptr_last->next;
	}
	ptr_last->next=nptr;
	nptr->next=root;
	total++;
	cout<<"Node added to End."<<endl;
	return root;
}

struct Node * addToMiddle(struct Node * nptr, int pos)
{
	struct Node * nptr_prev=NULL, * nptr_next=root;
	int count=1;
	while(count!=pos)
	{
		nptr_prev=nptr_next;
		nptr_next=nptr_next->next;
		count++;
	}
	nptr_prev->next=nptr;
	nptr->next=nptr_next;
	total++;
	cout<<"Node added in the Middle."<<endl;
	return root;
}

struct Node * addToList(struct Node * nptr, int pos)
{
  if(pos>total+1 || pos<1)
    {
      cout<<"Invalid Position. Could not add the node."<<endl;
      return root;
    }
  else
    {
    	if(pos==1)
    		return addToFront(nptr);
    	else if(pos==total+1)
    			return addToEnd(nptr);
    	else
    		return addToMiddle(nptr, pos);
    }
}

struct Node * deleteFirstNode(struct Node * ptr)
{
	struct Node * last_node=root;
	while(last_node->next!=root)
	{
		last_node=last_node->next;
	}
	if(ptr==last_node)
	{
		root=NULL;
		free(ptr);
		total--;
		cout<<"First and Last only node deleted."<<endl;
		return root;
	}
	else
	{
		root=ptr->next;
		last_node->next=root;
		free(ptr);
		total--;
		cout<<"First Node Deleted."<<endl;
		return root;
	}
}

struct Node * deleteLastNode(struct Node * ptr)
{
	struct Node * prev=root;

	while(prev->next!=ptr)
	{
		prev=prev->next;
	}
	prev->next=root;
	free(ptr);
	total--;
	cout<<"Deleted Last Node."<<endl;
	return root;
}

struct Node * deleteMiddleNode(struct Node * ptr)
{
	struct Node * prev, * next;
	prev=NULL;
	next=root;
	while(next!=ptr)
	{
		prev=next;
		next=next->next;
	}
	next=next->next;
	prev->next=next;
	total--;
	free(ptr);
	cout<<"Node deleted in the Middle."<<endl;
	return root;
}

struct Node * deleteFromList(int value)
{
  int count=1;
  struct Node * ptr=root;
  do
  {
  	if(ptr->data==value)
  		break;
  	else
  	{
  		count++;
  		ptr=ptr->next;
  	}
  }while(ptr!=root);

  if(count==1)
  	return deleteFirstNode(ptr);
  else if(count==total)
  		return deleteLastNode(ptr);
  else if(count>1 && count<total)
  			return deleteMiddleNode(ptr);
  else if(count>1 && ptr==root)
  	   {
  		 cout<<"Node not found. Nothing to delete."<<endl;
  		 return root;
  	   }
}

void printList()
{
  if(root==NULL)
    cout<<"List is empty"<<endl;
  else
    {
      struct Node * p=root;
      cout<<"Contents of the lists are "<<endl;
      do
	  {
	    cout<<p->data<<" "<<p->next->data<<endl;
	    p=p->next;
	  }while(p!=root);
    }
}

int get_element(int pos)
{
  struct Node * p=root;
  int count=0;
  while(count!=pos && p!=NULL)
    {
      p=p->next;
      count++;
    }
  return p->data;
}

void set_element(int pos, int val)
{
  struct Node * p=root;
  int count=0;
  while(count!=pos && p!=NULL)
    {
      p=p->next;
      count++;
    }
  p->data=val;
}

void merge(int l, int q, int r)
{
  int n1=q-l+1;
  int n2=r-(q+1)+1;
  int L[n1+1], R[n2+1];
  for(int i=0;i<n1;i++)
    L[i]=get_element(l+i);
  for(int j=0;j<n2;j++)
    R[j]=get_element(q+j+1);
  L[n1]=INF;
  R[n2]=INF;
  int i=0,j=0;
  for(int k=l;k<=r;k++)
    {
      if(L[i]<=R[j])
	  {
	    set_element(k,L[i]);
	    i++;
	  }
      else
	  {
	    set_element(k,R[j]);
	    j++;
	  }
    }
}

void mergesort(int left, int right)
{
  if(left< right)
    {
      int mid= (left+right)/2;
      mergesort(left, mid);
      mergesort(mid+1, right);
      merge(left, mid, right);
    }
}

int main(int argc, char * argv[])
{
  cout<<"Enter an option\n1-insert\n2-delete\n3-sort\n4-print\n5-exit"<<endl;
  int opt;
  cin>>opt;
  int val,pos;
  struct Node * np;
  while(opt!=5)
    {
      switch(opt)
	{
	   case 1: cout<<"Enter a value to be added in the list"<<endl;
	           cin>>val;
	           cout<<"Enter the position"<<endl;
		   	   cin>>pos;
		       np=createNode(val);
		       root=addToList(np,pos);
		       break;
	   case 2: cout<<"Enter a value to be deleted from the list"<<endl;
	           cin>>val;
	           root=deleteFromList(val);
		       break;
	   case 4: printList();
	           break;
	   case 3: if(total>0)
	             mergesort(0,total-1);
		       else
		         cout<<"Empty list. Nothing to sort"<<endl;
	           break;
	}
      cout<<"Enter an option\n1-insert\n2-delete\n3-sort\n4-print\n5-exit"<<endl;
      cin>>opt;
    }
  return 0;
}
