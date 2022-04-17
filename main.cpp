#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;

// Declare the variables
string username, password, buyOption;
int wallet = 1000000, quantity, productChosen, totalPrice, optionMenu, optionAuth, selectedProduct;
string userData[2];
map<string, string> listProduct[4];
queue<string> purchaseHistory;
bool isLogin;
bool inMenu = true;

void authMenu()
{
  cout << "\n-------- Marketplace Transaction --------\n\n";
  cout << "1. Register\n";
  cout << "2. Login\n";
  cout << "0. Exit\n";

  cout << "Input your choice: ";
  cin >> optionAuth;
  cout << "\n";
}

void homeMenu()
{
  cout << "\n-------- Home Page --------\n\n";
  cout << "1. Show Product List\n";
  cout << "2. Show Purchase History\n";
  cout << "0. Logout\n";

  cout << "Input your choice: ";
  cin >> optionMenu;
  cout << "\n";
}

// User authentication
void regist()
{
  cout << "Hello, Guest! Let's create your account\n";
  cout << "Input username: ";
  cin >> username;
  cout << "Input password: ";
  cin >> password;

  // input the username and password to userData array
  userData[0] = username;
  userData[1] = password;
}

void login()
{
  cout << "Hello! Login to your account below\n";
  cout << "Input username: ";
  cin >> username;
  cout << "Input password: ";
  cin >> password;

  if (userData[0] == username && userData[1] == password)
  {
    isLogin = true;
    cout << "Login success!\n";
    cout << "Hello, " << username << "!\n\n";
  }
  else
  {
    cout << "[!] Wrong password, try again!\n";
    authMenu();
  }
}

void auth()
{
  authMenu();
    switch (optionAuth)
    {
    case 1:
      regist();
      break;
    case 2:
      login();
      break;
    case 0:
      exit(0);
      break;
    default:
      cout << "[!] Please input the right choice";
    }
}

void initProduct()
{
  listProduct[0]["productName"] = "Shoes";
  listProduct[0]["productPrice"] = "130000";
  listProduct[0]["productQuantity"] = "100";

  listProduct[1]["productName"] = "Bag";
  listProduct[1]["productPrice"] = "250000";
  listProduct[1]["productQuantity"] = "3";

  listProduct[2]["productName"] = "Plain Shirt";
  listProduct[2]["productPrice"] = "50000";
  listProduct[2]["productQuantity"] = "100";

  listProduct[3]["productName"] = "Short Pants";
  listProduct[3]["productPrice"] = "50000";
  listProduct[3]["productQuantity"] = "100";
}

// Function to print map elements specified
// at the index, "index"
void print(map<string, string> myMap, int index)
{
  // Each element of the map is a pair
  // on its own
  cout << "(" << index << ")\n";
  for (auto pr : myMap)
  {
    cout << pr.first << "	 "
         << "  " << pr.second << '\n';
  }

  cout << '\n';
}

// Function to iterate over the map
// corresponding to an index
void showListProduct(map<string, string> *myContainer, int n)
{
  cout << "----- Product List -----\n\n";
  for (int i = 0; i < n; i++)
  {
    print(myContainer[i], i);
  }
}

void showq(queue<string> gq)
{
  cout << "--- Purchase History ---\n";
  queue<string> g = gq;
  if (g.empty())
  {
    cout << "[!] Empty purchase history\n";
  }
  while (!g.empty())
  {
    cout << g.front() << "\n";
    g.pop();
  }
}

void buyMenu()
{
  cout << "\nChoose product you want to buy (0/1/2/3): ";
  cin >> selectedProduct;

  if (selectedProduct > 3)
  {
    cout << "[!]  Please input the right product\n\n";
    showListProduct(listProduct, 4);
    buyMenu();
  }

  cout << "Input the quantity of the product you wanna buy: ";
  cin >> quantity;
  totalPrice = stoi(listProduct[selectedProduct]["productPrice"]) * quantity;
  cout << "\n";

  cout << "--- Price Details ---\n";
  cout << "Item(s) Name: " << listProduct[selectedProduct]["productName"] << "\n";
  cout << "Item(s) Price: " << listProduct[selectedProduct]["productPrice"] << "\n";
  cout << "Total Price: " << quantity << "*" << listProduct[selectedProduct]["productPrice"] << " = Rp" << totalPrice;

  cout << "\n\nYour Wallet: Rp" << wallet << "\n";
  cout << "Wanna buy it? (Y/N): ";
  cin >> buyOption;

  if (buyOption == "Y")
  {
    if (wallet < totalPrice)
    {
      cout << "[!] Your money isn't enough to buy the product(s)";
    }
    else
    {
      string productString = "Product: ";
      string productName = listProduct[selectedProduct]["productName"];
      string priceString = "Price per item: ";
      string productPrice = listProduct[selectedProduct]["productPrice"];
      string quantityString = "Quantity: ";
      string productQuantity = to_string(quantity);
      string buyDetails = productString + productName + "\n" + priceString + productPrice + "\n" + quantityString + productQuantity + "\n";
      purchaseHistory.push(buyDetails);
      wallet -= totalPrice;
      cout << "\nPurchase Completed\n";
      cout << "Your current wallet: " << wallet << "\n\n";
    }
  }
  else if (buyOption == "N")
  {
    showListProduct(listProduct, 4);
    buyMenu();
  }
  else
  {
    cout << "[!] Please input the right choice\n";
    showListProduct(listProduct, 4);
    buyMenu();
  }
}

void menu()
{
  inMenu = true;
  homeMenu();
  switch (optionMenu)
  {
  case 1:
    inMenu = false;
    showListProduct(listProduct, 4);
    buyMenu();
    menu();
    break;
  case 2:
    showq(purchaseHistory);
    break;
  case 0:
    exit(0);
    break;
  default:
    cout << "Please input the right choice";
  }
}

int main()
{
  initProduct();

  while (!isLogin)
  {
    auth();
  }

  while (inMenu)
  {
    menu();
  }

  return 0;
}
