// C++ program to encode and decode a string using
// Huffman Coding.
#include <bits/stdc++.h>
#define MAX_TREE_HT 256
#define STR_HISTOGRAM_MAX_TAM   (256)

using namespace std;

// to map each character its huffman value
map<char, string> codes;

// to store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct MinHeapNode
{
    char data;             // One of the input characters
    int freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, string str)
{
    if (root==NULL)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
    printCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;

        // reached leaf node
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans+'\0';
}

void strhist( string str, int hist[ STR_HISTOGRAM_MAX_TAM ] )
{
    memset( hist, 0, sizeof(int) * STR_HISTOGRAM_MAX_TAM );

    for (int i=0; i<str.size(); i++)
        hist[ str[i] ]++;
}


void exibir_histograma( int hist[STR_HISTOGRAM_MAX_TAM], int aux )
{
    int i = 0;
    int j = 0;

    for( i = 0; i < STR_HISTOGRAM_MAX_TAM; i++ )
    {
        if( (isprint(i)) && (hist[i] >= aux) )
        {
           cout << (char)i << " : " << hist[i];

            //for( j = 0; j < hist[i]; j++ )
              //  cout << " *";

           cout << "\n";
        }
    }
}

// Driver program to test above functions
int main(){

 /* String original */
    string str = "goiabada bananada panalada";

    cout << "Frase escrita:\n\n";
    cout << str << "\n\n";
    cout << "Frequência dos caracteres:\n\n";

     int h[ STR_HISTOGRAM_MAX_TAM ];

    /* Calcula histograma da string  */
    strhist( str, h );

    /* Exibe histograma das amostras com 2 ou mais ocorrencias */
    exibir_histograma( h, 1 );


    cout << "\nCaractere e seus códigos:\n\n";
    string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    cout << "\nCaractere e seus novos códigos:\n\n";
    for (auto v=codes.begin(); v!=codes.end(); v++)
        cout << v->first <<' ' << v->second << endl;

    for (auto i: str)
        encodedString+=codes[i];

    cout << "\nDados Huffman codificados:\n" << encodedString << endl;

    decodedString = decode_file(minHeap.top(), encodedString);
    cout << "\nDados Huffman decodificados:\n" << decodedString << endl;
    return 0;
}
