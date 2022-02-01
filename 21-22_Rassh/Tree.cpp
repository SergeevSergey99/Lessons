#includeiostream
using namespace std;

struct Node
{
    int value;

    Node left = nullptr;
    Node right = nullptr;
    
    Node(int val) 
    {
        value = val;
    }
    ~Node() 
    {
        if (left != nullptr)    delete left;
        if (right != nullptr)   delete right;
    }
};

struct Tree
{
    Node root = nullptr;
    
    ~Tree() 
    {
       delete root;
    }

    void Insert(int newValue)
    {
        if (root == nullptr)
            root = new Node(newValue);
        else
            InsertREC(root, newValue);
    }

    void PrintTree() 
    {
        if (root != nullptr)
            PrintTreeREC(root);
        cout  endl  endl;
    }
    int FindMin()
    {
      if (root == nullptr)
        throw invalid_argument( root does not exist );

      Node  min = FindMinREC(root);
      return min-value;    
    }
    
    int FindMax(){
      if (root == nullptr)
        throw invalid_argument( root does not exist );
      Node max = FindMaxREC(root);
      return max-value;
    }

    void Remove(int key){
      if (root == nullptr)
       return;
       RemoveREC(root,key);
    }
    

private


  Node  RemoveREC(Node  curr, int key){
    if(key  curr-value){
      curr-left = RemoveREC(curr-left, key);
    }
    else if (key  curr-value){
      curr-right = RemoveREC(curr-right, key);
    }
    else  key == curr-value
    {
      Node  l = curr-left;
      Node  r = curr-right;

      if(l == nullptr and r == nullptr)  
      {
          delete curr;
          return l;
      }
      else if(l == nullptr or r == nullptr){
        if(l == nullptr)
        {
          delete curr;
          return r;
        }
        else
        {
          delete curr;
          return l;
        }
        
      }
      else{

        Node  min = FindMinREC(curr-right);
        int tmp = curr-value;
        curr-value = min-value; 
        min-value = tmp;
        RemoveREC(curr-right, tmp);


      }
    }
    return curr;
  }

  Node  FindMinREC(Node  curr){
    if(curr-left != nullptr)
      return FindMinREC(curr-left);
    return curr;
  }


  Node FindMaxREC(Node curr){
    if(curr-right != nullptr){
      return FindMaxREC(curr-right);
    }
    return curr;
  }

    void InsertREC(Node current, int newValue)
    {
        if (current-value == newValue) return;

        if (current-value  newValue)
        {
            if (current-left == nullptr)
                current-left = new Node(newValue);
            else
                InsertREC(current-left, newValue);
        }
        if (current-value  newValue)
        {
            if (current-right == nullptr)
                current-right = new Node(newValue);
            else
                InsertREC(current-right, newValue);
        }
    }
    void PrintTreeREC(Node current) 
    {
        if (current-left != nullptr) PrintTreeREC(current-left);
        cout  current-value   ;
        if (current-right != nullptr) PrintTreeREC(current-right);
    }
};

void RandInsertTree(Tree& t, int length) {
    for (size_t i = 0; i  length; i++)
    {
        t.Insert(rand() % 100);
    }
}

int main() 
{
  srand(time(0));
  Tree t;

  RandInsertTree(t, 20);


  t.Insert(8);
  t.Insert(5);
  t.Insert(11);
  t.Insert(2);
  t.Insert(6);
  t.Insert(10);
  t.Insert(15);
  t.Insert(20);
  t.Insert(9);
  t.Insert(13);
  t.Insert(7);

  t.PrintTree();

  t.Remove(11);

  t.PrintTree();

  cout  t.FindMin()  endl;
  cout  t.FindMax()  endl;

}