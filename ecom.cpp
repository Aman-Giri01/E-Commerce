#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
using namespace std;
// ------------------------------------------------------------------------------------------------------------------------------------------
//===========================================================STOCK============================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------- 
class stock
{
 protected:
 int code,qty,num,qtty;
 float price,total_price,amt;
 string name;
 public:
//  --------------------------------------------------------HEART OF PROJECT-----------------------------------------------------------
 void status()
 {
    if(qty==0)
    cout<<"Unavailable";
    else
    cout<<"Available";
 }
 int get_code()
 { 
    return code;
 }
 string get_name()
 {
  return name;
 }
 int get_quanti()
 {
  return qty;
 }

 void get_quat()
 {
  cout<<"enter the quantity to purchase: ";
  cin>>qtty;
  if(qty>qtty)
  {
  qty=qty-qtty;
  total_price=price*qtty;
  cout<<"\n\t\t\t\tTotal Price to be paid: "<<total_price;
  a:
  cout<<"\n\t\t\t\tEnter amount to purchase item: ";
  cin>>amt;
  if(amt==total_price)
  {
    cout<<" \n\t\t\t\tItem Purchased Successfully..\nYour item will be delivered within 5 days\n";
  }
  else
  {
    cout<<"\nPlease pay sufficient amount.......\n";
    goto a;
  }
  }
  else
  cout<<"Insufficient quantity: ";
 }

 void removeQty()
 {
  qty=qty+qtty;
 }

 void showqty()
 {
   cout<<qtty<<setw(15);
   cout<<total_price;
 }
 void update_quantity()
 {
   int choice; 
   cout<<"Choose 1 for add and 2 for decrease quantity: ";
   cin>>choice;
   if(choice==1) 
   {
     cout<<"enter the quantity u want to increase: ";
     cin>>num;
     qty=qty+num;
   }
   else
   {
     cout<<"Enter the quantity u want to decrease: ";
     cin>>num;
     qty=qty-num;
   }
 }

 void getdata();
 void addTo_file();
 void show();
 void showdata();
 void search();
 void delete_data();
 void modify_data();
}s;
fstream file,temp;
// ---------------------------------------INPUT PRODUCT DETAILS----------------------------------------------------------------------
void stock::getdata()
{
  cout<<" Enter Code: ";
  cin>>code;
  get_code();
  cout<<"Enter Stock Name: ";
  cin>>name;
  get_name();
  cout<<"Enter Quantity: ";
  cin>>qty;
  get_quanti();
  cout<<"Enter Price: ";
  cin>>price;
  
}
// -------------------------------------------ADD PRODUCT DATA TO FILE-------------------------------------------------------------
void stock::addTo_file()
{
    char ch;
    ofstream fout("akhiri.txt",ios::app);
    fout.write((char*)&s,sizeof(s));
    cout<<"\nFile added successfully.\n";
    
    fout.close();
}
// ------------------------------------------------SHOW PRODUCT DATA--------------------------------------------------------------
void stock::show()
{
  cout<<code<<setw(8)<<name<<setw(13)<<price<<setw(10)<<qty<<setw(20);
  status();
  cout<<endl;
}
//----------------------------------------------READ PRODUCT DATA FROM FILE-----------------------------------------------------------
void stock::showdata()
{
    ifstream fin("akhiri.txt");
    if(!fin)
    {
        cout<<"File not Found.\n";
    }
    else
    {
        fin.read((char*)&s,sizeof(s));
        while(!fin.eof())
        {
            show();
            fin.read((char*)&s,sizeof(s)); 
        }
        fin.close();
    }

}
//----------------------------------------------SEARCH ANY PRODUCT BY CODE------------------------------------------------------------ 
void stock::search()
{
    int no,count=0;
    file.open("akhiri.txt",ios::in);
    if(!file)
    {
    cout<<"File not Found..\n";
    }
    else
    {
        cout<<"Enter item code to search: ";
        cin>>no;
        file.read((char*)&s,sizeof(s));
        while(!file.eof())
        {
            if(no==get_code())
            {
                count=1;
                cout<<"-------------------------------------------------------------------------------------\n";
                cout<<setw(6)<<"Code"<<setw(15)<<"Name"<<setw(6)<<"Quantity"<<setw(15)<<"Price"<<setw(6)<<"Status\n";
                cout<<"-------------------------------------------------------------------------------------\n";
                show();
                cout<<"-------------------------------------------------------------------------------------\n";
                break;
            }
             file.read((char*)&s,sizeof(s));
        }
            if(count==0)
            {
                cout<<"Item not Found.\n";
            }
        file.close();    
    }
}
// ---------------------------------------DELETE A PRODUCT BY ITEM CODE---------------------------------------------------------
void stock::delete_data()
{
    int no;
    cout<<"Enter Item code to delete: ";
    cin>>no;
    ofstream file2;
    file2.open("temp.txt",ios::out);
    file.open("akhiri.txt",ios::in);
    if(!file)
    {
        cout<<"File not found.\n";
    }
    else
    {
        int count=0;
        file.read((char*)&s,sizeof(s));
        while(!file.eof())
        {
            if(no!=get_code())
            {
              file2.write((char*)&s,sizeof(s)); 
              count++;
            }
           
            file.read((char*)&s,sizeof(s));
        }
         if(count==1)
            {
              cout<<"\nItem code not found...\n";
            }
          else
           {  
              cout<<"\nSuccessfully deleted.................\n";
           }
    }
    file2.close();
    file.close();
    remove("akhiri.txt");
    rename("temp.txt","akhiri.txt");

}
// ----------------------------------------MODIFY PRODUCT DETAILS BY NAME ,PRICE AND QUANTITY---------------------------------------
void stock::modify_data()
{
    int no,ch,flag=0;
    float p;
     char n[20];
      file.open("akhiri.txt",ios::in|ios::out);
      cout<<"Enter the item code of item which you want to update: "<<endl;
      cin>>no;
     file.read((char*)&s,sizeof(s));
  while(!file.eof())
  {
    int pos=file.tellp();
    if(no==get_code())
    {
      
      cout<<"select one which you want to change"<<endl;
      cout<<"1.Item name"<<endl;
      cout<<"2.Item Price "<<endl;
      cout<<"3.Item quantity"<<endl;
      cout<<"enter your choice..."<<endl;
      cin>>ch;
      switch(ch)
      {
       case 1:
      cout<<"enter new Item name: "<<endl;
      cin>>n;
      name=n;
       file.seekp(pos-sizeof(s));
      file.write((char*)&s,sizeof(s));
      flag++;
      break;
      case 2:
      cout<<"enter new price: "<<endl;
      cin>>p ;
      price=p;
      file.seekp(pos-sizeof(s));
      file.write((char*)&s,sizeof(s));
      flag++;
      break;
      case 3:
      update_quantity();
      file.seekp(pos-sizeof(s));
      file.write((char*)&s,sizeof(s));
      flag++;
      break;
      default:cout<<"enter right choice..."<<endl;
    }
    }
    file.read((char*)&s,sizeof(s));
  }
      file.close();
      if(flag==0)
      {
        cout<<"Record not found! "<<endl;
      }
      else
      cout<<"Record update successfuly"<<endl;
}
// ------------------------------------------------------------------------------------------------------------------------------------------
//===========================================================CUSTOMER CLASS============================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------- 

class customer:public stock
{
  protected:
   string name,email;
   char item[20];
   long long ph;
   char add[20];
   int qty,price,count=0;
  public:
   string cname()
   {
     return name;
   }
  void cus();
  void cshow();
  void purchase();
  void returnP();
  void showPurchase();
  void allPurDetails();
  string get_name()
  {
    return name;
  } 
}c;
// -----------------------------------------------------------INPUT CUSTOMER DATA------------------------------------------------------------
void customer:: cus()
{
  cout<<"Enter Name: ";
  cin>>name;
  cname();
  cout<<"Enter Phone no.: ";
  cin>>ph;
  cout<<"Enter E-mail: ";
  cin>>email;
  cout<<"Enter Address: ";
  cin>>add;
  cout<<endl;
}
// ---------------------------------------------------SHOW CUSTOMER DATA---------------------------------------------------------------
void customer::cshow()
{
  cout<<endl;
  cout << setw(6) << name << setw(10) << add<< setw(10) << ph<< setw(10) << email<< setw(15) <<item <<setw(15);//<<qty<<setw(10)<<price<< endl;
  s.showqty();
  cout<<endl; 
}
// ---------------------------------------------------PURCHASE ITEM-------------------------------------------------------------------
void customer::purchase()
{
  int pos;
  ofstream out("customer.txt",ios::app);
  file.open("akhiri.txt",ios::out | ios::in);
  if(!file)
  {
    cout<<"\n file doesnot exist..\n";
  }
  else{
  cout<<"Enter Item name to purchase: ";
  cin>>item;
  cus();
  file.read((char*)&s,sizeof(s));
  while(!file.eof())
  {
    pos=file.tellp();
    if(item==s.get_name())
     {
       cout<<endl;
       s.get_quat(); 
       file.seekp(pos-sizeof(s));
       file.write((char*)&s,sizeof(s));
       out.write((char*)&c,sizeof(c));
       count++;
     }
     file.read((char*)&s,sizeof(s));
  }
  if(count==0)
  {
    cout<<"\nSorry Item not available..\n";
  }
  file.close();
  out.close();
  }
}
// --------------------------------------------SHOW PURCHASE DETAILS OF CUSTOMER BY CUSTOMER'S NAME-------------------------------------------------------------
void customer::showPurchase()
{
  int count=0;
  char name[20];
  ifstream in("customer.txt",ios::app);
  cout<<"enter name of the customer: ";
  cin>>name;
  in.read((char*)&c,sizeof(c));
  while(!in.eof())
  {
   if(name==cname())
   {
      cout << "-------------------------------------------------------------------------------------\n";
      cout << setw(6) << "Name" << setw(10) << "Address" << setw(10) << "Ph.No." << setw(10) << "Email" << setw(15) << "Item"<<setw(15)<<"Qty"<<setw(18)<<"TotalPrice" << endl;
      cout << "-------------------------------------------------------------------------------------\n";
      cshow();
      count++;
   }
   in.read((char*)&c,sizeof(c));
  }
  if(count==0)
  {
    cout<<" \nNo purchase available...\n";
  }
  in.close();
}
  // ---------------------------------------------------------RETURN PURCHASE ITEM----------------------------------------------------
void customer::returnP() {
    int pos;
    string name;
    ofstream out("temp.txt", ios::out); // Temporary file to rewrite customer data

    file.open("akhiri.txt", ios::out | ios::in);
    cout << "Enter name of the customer: ";
    cin >> name;
    if (!file) {
        cout << "\n File does not exist..\n";
    } else {
        file.read((char*)&s, sizeof(s));
        while (!file.eof()) {
            pos = file.tellp();
            if (name == cname()) {
                cout << "-------------------------------------------------------------------------------------\n";
                cout << setw(6) << "Name" << setw(10) << "Address" << setw(10) << "Ph.No." << setw(10) << "Email" << setw(15) << "Item" << setw(15) << "Qty" << setw(18) << "TotalPrice" << endl;
                cshow();
                cout << "Press 1 for return your product: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    s.removeQty(); // Update stock's quantity when returning
                    file.seekp(pos - sizeof(s));
                    file.write((char*)&s, sizeof(s));
                    cout << "\n successfully cancelled!\nYour amount will be refunded within 5 working days.\n";
                } else {
                    // Copy non-matching customer data to the temporary file
                    out.write((char*)&c, sizeof(c));
                }
            } else {
                // Copy non-matching customer data to the temporary file
                out.write((char*)&c, sizeof(c));
            }
            file.read((char*)&s, sizeof(s));
        }
        file.close();
        out.close();
    }
    remove("customer.txt"); // Delete the original customer file
    rename("temp.txt", "customer.txt"); // Rename the temporary file to customer.txt
}
// --------------------------------------SHOW ALL CUSTOMER'S PURCHASE DETAILS------------------------------------------------------------
void customer::allPurDetails()
{
  int count=0;
  ifstream in("customer.txt",ios::app);
  in.read((char*)&c,sizeof(c));
  while(!in.eof())
  {
      cout << "-------------------------------------------------------------------------------------\n";
      cout << setw(6) << "Name" << setw(10) << "Address" << setw(10) << "Ph.No." << setw(10) << "Email" << setw(15) << "Item"<<setw(15)<<"Qty"<<setw(18)<<"TotalPrice" << endl;
      cout << "-------------------------------------------------------------------------------------\n";
      cshow();
      count++;
      in.read((char*)&c,sizeof(c));
  }
  if(count==0)
  {
    cout<<" \nNo purchase available...\n";
  }
  in.close();
}
// ------------------------------------------------------------------------------------------------------------------------------------------
//====================================================CUSTOMER'S AUTHENTICATION=========================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------- 
class User {
public:
    string username;
    string password;

    User(const string& u, const string& p) : username(u), password(p) {}
};
class UserDatabase {
public:
// ----------------------------------------------REGISTRATION--------------------------------------------------------------------------
    int registerUser(const User& user) {
         string username, password;
            User newUser(username, password);
        ofstream file("users.txt", ios::app);
        if (!file) {
            cerr << "Error: Could not open the user database file." << endl;
            return false;
        }

        file << user.username << " " << user.password << endl;
        file.close();
        return true;
    }
// -------------------------------------------------LOGIN------------------------------------------------------------------------------
    int loginUser(const string& username, const string& password) {
        ifstream file("users.txt");
        if (!file) {
            cerr << "Error: Could not open the user database file." << endl;
            return false;
        }

        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
};
// ------------------------------------------------------------------------------------------------------------------------------------------
//========================================        MAIN    =========================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------- 
int main()
{

 UserDatabase database;
 string user,pass;int count=0;
 int choose;system("color 06");
    cout<<"\n:****************************************************************************************:\n";
    cout<<"\n                   || WELCOME TO A4 E-COMMERCE WEBSITE ||\n\n";
     cout<<"\n                         || PROJECT BY:- ||\n";
    cout<<"\n                        || AMAN KR. GIRI || ";
    cout<<"\n:****************************************************************************************:\n";    
    sleep(4); system("cls");
    z:
    system("cls");
    system("color 02");
    cout<<"\n\n\n:****************************************************************************************:\n";
    cout<<"\n:                               1.STAFF                                                    :\n";
    cout<<":                               2.CUSTOMER                                                 :\n";
    cout<<"\n:****************************************************************************************:\n";
    cout<<"\n--------------------------CHOOSE 1 OR 2: "  ;
    //system("cls");
    cin>>choose;
    system("cls");
    if(choose==1)
  {
    // --------------------------------------------------STAFF PORTION -------------------------------------------------------------------
      p:
      cout<<"Enter Username: ";
      cin>>user;
      cout<<"Enter Password: ";
      cin>>pass;
      if(user!="aman"||pass!="123")
       {
         cout<<"Please enter valid username or pass\n";
         system("cls");
         goto p;
       }
     else
     {
        int choice;
        do
        {system("color 09");
          cout<<"----------------------------------------------------------------------------------------------\n";
          cout<<":*******************************   MENU   ****************************************************:\n";
          cout<<":                            1.ADD ITEM IN STOCK                                              :\n";
          cout<<":                            2.SHOW ALL AVAILABLE PRODUCTS                                    :\n";
          cout<<":                            3.SEARCH A PRODUCT                                               :\n";
          cout<<":                            4.MODIFY A PRODUCT                                               :\n";
          cout<<":                            5.DELETE A PRODUCT                                               :\n";
          cout<<":                            6.SHOW ALL PURCHASE DETAILS OF CUSTOMERS                         :\n";
          cout<<":                            7.GO TO MAIN MENU                                                :\n";
          cout<<":                            8.EXIT                                                           :\n";
          cout<<":*********************************************************************************************:\n";
          cout<<"----------------------------------------------------------------------------------------------\n";
          cout<<"\n--------------------------ENTER YOUR CHOICE(1,2,3,4,5,6,7,8): ";
          cin>>choice;
       switch(choice)
    {
      case 1:
       s.getdata();
       s.addTo_file();
       system("pause");
       system("cls");
       break;
      case 2:
       s.showdata();
      system("pause");
      system("cls");
       break;
      case 3:
       s.search();
       system("pause");
       system("cls");
       break;
      case 4:
       s.modify_data();
       system("pause");
       system("cls");
       break;
      case 5:
       s.delete_data();
       system("pause");
       system("cls");
       break;
      case 6:
       c.allPurDetails();
       system("pause");
       system("cls");
       break; 
      case 7:
       goto z;
       system("pause");
       system("cls");
       break; 
      case 8:
       system("cls");
       cout<<"\n\n\n\n\n...............................THANKS FOR USING AMANS' & AFROJ'S PROGRAM.............................\n";
       exit(0);
      default:
       cout<<"INVALID CHOICE....\n";
    }
   }while(choice!=8);
     }
  }
  else if(choose==2)
  {
    // ------------------------------------------------------ CUSTOMER PORTION--------------------------------------------------
    while (true) {
        system("color 07");
        cout<<"\nNOTE: IF YOU ARE NEW USER THEN DO REGISTRATION FIRST BEFORE LOGIN INTO THIS WEBSITE\n";
        cout<<"\n----------------------------------------------------------------------------------------------\n";
        cout<<":*********************************************************************************************:\n\n";
        cout<<":                            1.REGISTER                                                       :\n";
        cout<<":                            2.LOGIN                                                          :\n";
        cout<<":                            3.EXIT                                                           :\n\n";
        cout<<":*********************************************************************************************:\n";
        cout<<"----------------------------------------------------------------------------------------------\n";
        int cchoice;
        cout<<"\n--------------------CHOOSE ONE OF THE FOLLOWING(1,2,3): ";
        cin >> cchoice;

        if ( cchoice == 1) {
          system("cls");
            string username, password;
            cout<<"\n-----------------------------------------------------------------------------------------------------\n";
            cout << "                                    Enter username: ";
            cin >> username;
            cout << "                                    Enter password: ";
            cin >> password;
            cout<<"\n-----------------------------------------------------------------------------------------------------\n";
            User newUser(username, password);
            if (database.registerUser(newUser)) {
                cout << "                                Registration successful!\n" << endl;
            } else {
                cerr << "                              Registration failed.\n" << endl;
            } sleep(1);
        } else if (cchoice == 2) {
            string username, password;
            system("cls");
            cout<<"\n-----------------------------------------------------------------------------------------------------\n";
            cout << "                                       Enter username: ";
            cin >> username;
            cout << "                                       Enter password: ";
            cin >> password;
            if (database.loginUser(username, password)) {
               cout<<"\n--------------------------------------------------------------------------------------------------\n";
                cout << "                                  Login successful!\n" << endl;
                cout<<"\n                                   Welcome "<<username<<" !\n";
                sleep(2);

      int cuschoice;
    do{
                system("cls");system("color 06");
                 cout<<"\n----------------------------------------------------------------------------------------------\n";
                 cout<<":*******************************   MENU   ****************************************************:\n\n";
                 cout<<":                            0.SHOW ALL ITEMS                                                 :\n";
                 cout<<":                            1.PURCHASE                                                       :\n";
                 cout<<":                            2.CANCEL                                                         :\n";
                 cout<<":                            3.SEARCH YOUR ITEM                                               :\n";
                 cout<<":                            4.GO TO MAIN MENU                                                :\n";
                 cout<<":                            5.EXIT                                                           :\n\n";
                 cout<<":*********************************************************************************************:\n";
                 cout<<"----------------------------------------------------------------------------------------------\n";
                 cout<<"\n--------------------------ENTER YOUR CHOICE(1,2,3,4,5): ";
                cin>>cuschoice;
       switch(cuschoice)
    {
      case 0:
       system("cls");
       cout<<"-------------------------------------------------------------------------------------\n";
       cout<<"CODE"<<setw(10)<<"NAME"<<setw(15)<<"PRICE"<<setw(15)<<"QUANTITY"<<setw(15)<<"STATUS"<<setw(10)<<"\n";
       cout<<"-------------------------------------------------------------------------------------\n";
       s.showdata();
       cout<<"-------------------------------------------------------------------------------------\n";
       system("pause");
       system("cls");
       break;
      case 1:
       c.purchase();
       system("pause");
       system("cls");
       break;
      case 2:
       c.returnP();
      system("cls");
      system("pause");
      system("cls");
       break;
      case 3:
       c.showPurchase();
       system("pause");
       system("cls");
       break;
      case 4:
       goto z;
       system("pause");
       system("cls");
       break;  
      case 5:
       system("cls");
       cout<<"\n\n\n\n******************************************     THANK YOU    ***************************************************\n";
       cout<<"\n*****************************************     VISIT  AGAIN  *************************************************** \n\n\n";
       break;       
       default:
       cout<<"\nPLEASE ENTER VALID CHOICES\n";   
   }
    }while(cuschoice!=5);
       break;

   } else {
                count++;
                if(count==2)
                {
                  for(int i=20;i>=0;i--)
                  {
                    cout<<"\nRetry After 20 seconds:  ";
                    cout<<"00:"<<i;
                    sleep(1);
                    system("cls");
                  }
                }
                else
                {
                   cerr << "Login failed. Please check your credentials." << endl;
                  sleep(1);
                }
           }
        } else if (cchoice == 3) {
            break;
        } 
        else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
  }
  else
  {
    cout<<"PLEASE ENTER ONLY 1 AND 2..";
  }
}
