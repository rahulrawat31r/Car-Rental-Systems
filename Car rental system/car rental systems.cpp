#include <iostream>
#include <fstream>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
using namespace std;

string extension = ".txt";
string car_folder = "cars\\";
string list = "cars\\cars list.txt";
string test_text = "cars\\new_car.txt";
string current_licence;
int profit = 0;
int balance;

void starter (){
    fstream file;
    file.open ("shop.txt");
    string data;

    file >> data;
    balance = stoi (data);
    file.close ();
}

void loading ();
void bill_generator (string,int,int,string);
void shop_balance (int);
void return_bill_generator (string, string );
void get_menu (){
    system ("cls");
    cout << "\n\n\n\n\t\t\t\t  GETTING MENU READY  ";
    for (int i=0;i<3;i++){
        sleep (1);
        cout<<" .";

    }
}
void selling_bill_generator (string model , int quantity, int price, string licence ){
    system ("cls");
    cout << "\t\t\t\t || Final BILL || \n\n";
    fstream file,file2;
    string s = car_folder + model + extension;
    file.open (s);
    s = "customers\\";
    s = s + licence + extension;
    file2.open (s);
    srand (time(0));
    string data;
    int value;
    float pricing = price;
    float valuing;
    cout <<"\t\t\t\t\t|| R Sales Corporation Pvt. Limited ||"<<endl<<endl;

    cout <<"Buyers Information -- > "<<endl<<endl;
    cout << "Licence no. ---> "<< licence<<endl;
    file2 >> data;
    file2 >> data;
    cout <<"Name -- > "<<data<<endl;
    file2 >> data;
    cout << "Age --> "<<data<<endl<<endl;

    file2.close ();

    cout << "Vehicle Information --> "<<endl<<endl;
    cout << "Model --> "<<model<<endl;
    file >> data;
    file >> data;
    cout << "Actual Value -- > "<<data<<endl;
    cout << "Current Market Value -- > "<<price<< endl;
    value = stoi (data);
    valuing = value;
    cout << "Total Price Drop -- > "<< (100 - (((pricing)/(valuing))*100))<<" %\n";
    file >> data;
    cout << "Vehicle Company -- > "<<data<<endl<<endl;
    cout << "Total to pay --> "<<price*quantity<<" Rs only /-"<<endl;
    cout << "\t\t\t|| Deal Success ||"<<endl<<endl;
    file.close ();

}

class cars {
    public:
        void available_cars (int);
        void new_car_addition ();
        int replace_cars_content (string, int , int , int );
        void set_car_data (string);
        int isempty ();
        void car_details (string);
};

void cars :: car_details (string model){
    fstream file,checker;
    checker.open (list);
    int counter = 0;
    string test;
    while (!checker.eof ()){
        checker >> test;
        if (test == model){
            counter ++ ;
            break;
        }
    }

    checker.close ();
    if (counter != 0){
        string t = car_folder + model ;
        t = t + extension;
        file.open (t);

        cout << "\t\t\t\t || Details are --- > || " << endl<<endl;
        cout << "Model Name -- > "<< model<<endl;
        file >> t;
        file >> t;
        cout << "Selling Price --> "<<t<<endl;
        file >> t;
        cout << "Company --> "<<t<<endl;

        file.close ();
    }

    else {
        cout << endl << "We are currently not dealing with that car !"<< endl;
    }

}

void cars :: available_cars (int y){
    // system ("cls");
    cout<<"\n\n\t\t\t\tAvailable Cars are -- >\n\n\n";
    ifstream cars_list;

    cars_list.open(list);
    
    string text = "None";
    while (!cars_list.eof()){
        cars_list >> text;
        if (y!=1){
            if (text == "0"){
                cars_list>> text;
                continue;
            }
        }
        cout<<"Quantity --> "<<text<<"    ";
        cars_list>> text ;
        cout<<"Model --> "<< text<<endl;
    }

    cars_list.close();


}

int cars :: replace_cars_content (string name, int new_value, int operation, int checking){
   fstream fcopy, tcopy;

   fcopy.open (list);
   tcopy.open (test_text,ios :: out);

   int counter = 0, final_counter = 0;
   string qunatity, model;

   int q, i = 0;
    while (!fcopy.eof ()){
        fcopy >> qunatity;
        fcopy >> model;

        q = stoi (qunatity);
        if (model == name ){
            counter ++ ;
            if (operation == 1){
                q = q + new_value;
            }
            else {
                q = q - new_value;
            }

            if (q >= 0){
                qunatity = to_string (q);
            }
            
            else {
                cout << endl << "Insufficient stock available !"<<endl;
                final_counter ++ ;
            }

            if (i == 0){
                tcopy << qunatity;
            }
            else  {
                tcopy << endl << qunatity;
            }

            tcopy << " ";
            tcopy << model;
        }

        else {
            if (i == 0)
                tcopy <<  qunatity;
            else  
                tcopy << endl << qunatity;
            
            tcopy << " ";
            tcopy << model;

        }

        i ++ ;
    }

   if (checking == 1){
      if (counter == 0){
         cout << "We are currently not dealing with that vehicle !"<<endl;
         final_counter ++ ;
      }
   }

   else {
      if (counter == 0){
         qunatity = to_string (new_value);
         tcopy << endl << qunatity;
         tcopy << " ";
         tcopy << name;

         set_car_data (name);
      }
   }

   fcopy.close ();
   tcopy.close ();

   remove (list.c_str());
   rename (test_text.c_str(),list.c_str());

   if (final_counter == 0){
    return 1;
   }
   return 0;
}


class customers {
    public :

        void renters ();
        void buyers ();
        void returners ();
        void sellers ();
        void customer_registrationss (string);
        int check_new_customer (int);
        void visit_caretaker (string);
        string name_finder (string);
        void customer_data (string);
        int discount_calculator (string, string);

};

void customers :: sellers (){
    string model;
    int number,bill;
    cout<<"Enter the model of the car : ";
    cin>>model;

    cout<<"Enter the number of cars: ";
    cin>> number;
    string q = to_string (number);
    cars c;
    int x = c.replace_cars_content (model,number, 1,1);

    if (x!=0){
        bill = discount_calculator (model,"1234");
        selling_bill_generator (model,number,bill,current_licence);
        shop_balance (-bill*number);
        cout<<"Thanks for dealing with us !"<<endl;
    }

}

void customers :: renters (){
    cars c;
    int bill,price;
    c.available_cars (0);

    string model;
    int number;

    cout<<"Enter the model of the car: ";
    cin>>model;

    cout<<"Enter the number of cars: ";
    cin>> number;

    bill = c.replace_cars_content (model, number, 0,1);
    if (bill){
        price = discount_calculator (model,current_licence);
        bill_generator (model,number,price/1.2,current_licence);
        shop_balance ((price/1.2)*number);
    }
        

}

void customers :: buyers (){
    cars c;
    int bill,price;
    c.available_cars (0);

    string model;
    int number;

    cout<<"Enter the model of the car: ";
    cin>>model;

    cout<<"Enter the number of cars: ";
    cin>> number;

    bill = c.replace_cars_content (model, number, 0,1);
    if (bill){
        price = discount_calculator (model,current_licence);
        bill_generator (model,number,price,current_licence);
        shop_balance ((price)*number);
    }
}

void customers :: returners (){
    string model;
    int number;

    cout<<"Enter the model of the car: ";
    cin>>model;

    cout<<"Enter the number of cars: ";
    cin>> number;
    string q = to_string (number);
    cars c;
    int x = c.replace_cars_content (model, number, 1,1);
    if (x!=0)
        return_bill_generator ( model , q );

    cout<<"Thanks for dealing with us !"<<endl;
}

void cars:: new_car_addition(){
    customers cs;
    system ("cls");
    cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
    cout<<"\n\n\n\t\t\t\tCAR INCLUSION FORM -- > \n\n"<<endl;
    available_cars (1);

    cout<<endl<<"Do you want to add new car model (1) or \nWanted to increase the quantity of already present car (2): ";
    int input, number_of_cars,y;
    cin>>input;
    cout << endl;
    fstream adding;
    int bill;

    string name,x;
    switch (input){
        case 1:
            
            adding.open (list,ios :: app);
            cout<<"Enter the model of the car (in Captial): ";
            cin>>name;

            cout<<"Enter the number of cars to add: ";
            cin>>x;
            y = stoi (x);
            x = x + " ";
            x = x + name;
            adding << endl <<x;
            adding.close();

            set_car_data (name);
            cout<<endl <<x<< "'s have been successfully added to the stock !"<<endl;

            cout << endl << endl;
            bill = cs.discount_calculator (name,"Rahul_Owner");
            bill_generator (name,y,bill/3,"Rahul_Owner");
            shop_balance (-((bill/3)*y));
            break;

        case 2:
            if (isempty ()){
                break;
            }

            cout<<"Enter the model of the car: ";
            cin>>name;

            cout<<"Enter the number of cars to add to the current stock: ";
            cin>>x;
            number_of_cars = stoi (x);

            x = x + " ";
            x = x + name;
            bill = replace_cars_content (name, number_of_cars,1,1);
            if (bill == 1){
                bill = cs.discount_calculator (name,"Rahul_Owner");
                bill_generator (name,number_of_cars,bill/3,"Rahul_Owner");
                shop_balance (-((bill/3)*number_of_cars));
            }
            
            break;

        default : 
            cout<<"Invalid Input !"<<endl;
            break;
    }

    system ("PAUSE");
}



void customers :: customer_registrationss (string licence) {
    system ("cls");
    cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
    cout <<"\t\t\tNew Customer Registration Section --- >\n\n\n";
    fstream files;
    string a = "customers\\";
    string l = licence;
    string add = ".txt";
    a = a + l;
    a = a + add;
    files.open (a,ios :: out);
    files << licence <<endl;

    string data;
    cout<<"Enter the name of the customer: ";
    cin>>data;
    files << data << endl;

    cout<<"Enter the age of the customer: ";
    cin>>data;  
    files << data <<endl;

    data = "0";
    files << data ;

    files.close ();
    files.open ("customers\\all customers.txt", ios :: app);
    files << endl << licence;
    files.close ();


}

int customers :: check_new_customer (int y){
    cout<<"\t\t\t\t || Customers Section ||\n\n\n";

    string data, checker;

    cout<<"Enter the licence of the customer: ";
    cin >> data;
    current_licence = data;
    fstream file;
    file.open ("customers\\all customers.txt");

    int counter = 0;

    while (!file.eof ()){
        file >> checker;

        if (checker == data){
            counter ++ ;
            break;
        }
    }
    
    if (y == 1){
        if (counter == 0){
            return 1;
        }
    }
    if (counter == 0){
        customer_registrationss (data);
        loading ();
        system ("cls");
        cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
    }
    
    cout << "\t\t\t\t\t\t || Customer Section ||\n\n\n";
    string customer_name = name_finder (data);
    cout << "Welcome, "<<customer_name<<" !"<<endl;
    visit_caretaker (data);

    customer_data (data);

    file.close ();

    return 0;
}

void customers :: visit_caretaker (string licence){
    fstream file, new_file;
    string s = "customers\\";
    string data;
    string t = ".txt";
    s = s + licence;
    s = s + t;

    file.open (s);
    new_file.open ("test.txt",ios::out);

    for (int i = 0; i<3; i++){
        if (i != 0){
            new_file << endl;
        }

        file >> data;
        new_file << data;
    }

    file >> data;
    int i = stoi (data);
    i ++ ;
    data = to_string (i);
    new_file << endl << data;
    file.close ();

    remove (s.c_str());
    new_file.close ();

    rename ("test.txt", s.c_str ());
}

void loading (){
    cout<<"\n\n\t\t\t\t Loading Data  ";
    for (int i=0;i<3;i++){
        sleep (1);
        cout<<". ";
    }
    cout<<endl;
    // system ("PAUSE");

}

string customers :: name_finder (string licence){
    fstream file;
    string s = "customers\\";
    string t = ".txt";
    s = s + licence;
    s = s + t;

    file.open (s);
    for (int i=0;i<2;i++){
        file >> s;
    }

    file.close ();
    return s;
}

void customers :: customer_data (string licence ){
    string s = "customers\\";
    string t = ".txt";
    s = s + licence;
    s = s + t;

    cout<<endl;

    fstream file;
    file.open (s);
    file >> s;
    cout<<"Licence No. --> "<<s<<endl;
    file >> s;
    file >> s;
    cout<<"Age -- > "<<s<<endl; 
    file >> s;
    cout << "Visits --> "<<s<<endl;
    file.close ();

}

void exiting (){
    cout<<"\n\n\t\t\t\t Exiting from program  ";
    for (int i=0;i<3;i++){
        sleep (1);
        cout<<". ";
    }
    cout<<endl;
}

void cars :: set_car_data (string name){
    fstream carfile;

    string data,t;
    data = car_folder + name;
    data = data + extension;
    carfile.open (data,ios :: app);
    carfile.seekg (0,ios :: beg);

    carfile << name << endl;

    cout <<"Enter the selling price of the car: ";
    cin>>data;

    carfile << data << endl;

    cout << "Enter the company of the car: ";
    cin>>data;
    carfile << data;

    carfile.close ();

}

int cars :: isempty (){
    fstream file;
    file.open (list);
    string t;
    file >> t;
    if (t == ""){
        cout << "No Stock !"<<endl;
        return 1;
    }

    file.close ();
    return 0;
}

int customers :: discount_calculator (string model, string licence){
    int visits=0, price,discount;
    fstream File;
    string t = "customers\\";
    if (licence != "1234"){
        t = t + licence;
        t = t + ".txt";
        File.open (t);

        for (int i=0;i<4;i++){
            File >> t;
        }

        visits = stoi (t);
        File.close ();
    }
    t = car_folder + model;
    t = t + ".txt";
    File.open (t);

    for (int i=0;i<2;i++){
        File >> t;
    }

    price = stoi (t);
    
    if (visits < 20)
         discount = ((visits)/4)*5;
    else {
        discount = 20;
    }
    
    if (licence == "1234"){
        price = ((price*(100-30))/100);
    }
    else
        price = ((price*(100-discount))/100);

    return price;
}

void bill_generator (string model , int quantity, int price, string licence ){
    system ("cls");
    cout << "\t\t\t\t || Final BILL || \n\n";
    fstream file,file2;
    string s = car_folder + model + extension;
    file.open (s);
    s = "customers\\";
    s = s + licence + extension;
    file2.open (s);
    srand (time(0));
    string data;
    int value;
    float pricing = price;
    float valuing;
    cout <<"\t\t\t\t\t|| R Sales Corporation Pvt. Limited ||"<<endl<<endl;

    cout <<"Buyers Information -- > "<<endl<<endl;
    cout << "Licence no. ---> "<< licence<<endl;
    file2 >> data;
    file2 >> data;
    cout <<"Name -- > "<<data<<endl;
    file2 >> data;
    cout << "Age --> "<<data<<endl<<endl;

    file2.close ();

    cout << "Vehicle Information --> "<<endl<<endl;
    cout << "Model --> "<<model<<endl;
    file >> data;
    file >> data;
    cout << "Actual Value -- > "<<data<<endl;
    cout << "Discouted Value -- > "<<price<< endl;
    value = stoi (data);
    valuing = value;
    cout << "Total Avail Discount -- > "<< (100 - (((pricing)/(valuing))*100))<<" %\n";
    file >> data;
    cout << "Vehicle Company -- > "<<data<<endl;
    cout << "Number of vehicles -- > "<< quantity << endl<<endl;
    cout << "Total to pay --> "<<price*quantity<<" Rs only /-"<<endl;
    cout << "\t\t\t|| Deal Success ||"<<endl<<endl;
    file.close ();

}


void shop_balance (int price){
    fstream file, file2;
    file.open ("shop.txt");
    file2.open ("new shop.txt",ios::out);
    string data;
    int value;

    file >> data;
    value = stoi (data);
    value = value + price;
    
    profit = profit + price;
    
    data = to_string (value);
    file2 << data;

    file.close ();
    file2.close ();
    remove ("shop.txt");
    rename ("new shop.txt","shop.txt");

}

void return_bill_generator (string model, string quantity){
    fstream file;
    string path = car_folder + model + extension ;
    file.open (path);
    file >> path;
    file >>  path;
    int x = stoi (path);
    int y = stoi (quantity);
    cout <<"\t\t\t\t\t|| R Sales Corporation Pvt. Limited ||"<<endl<<endl;

    cout << "Name -- > "<< model << endl;
    cout << "Please Collect --> "<< (x*y)/2 << endl << endl;

    cout << "\t\t\t|| Thanks for Dealing with us ||"<<endl;
    shop_balance (-((x*y)/2));
    file.close ();
}

int main (){
    starter ();
    system ("cls");

    loading ();
    

    int input = 0,customer_checker;
    string taker;
    cars c;
    customers s;
    while (input != 9){
        system ("cls");
        cout<<"\t\t\t\t !!! WELCOME !!!\n\n\n\n\n";

        cout<<"Enter the operation you want to perform\n\n";

        cout<<"1 for checking Availability\n"<<"2 For increasing Stock"<<endl;
        cout<<"3 for Renting Car menu"<<endl;
        cout<<"4 for buying car menu\n5 for Returning the car\n6 For Selling\n7 for checking profit and balance\n8 for Getting car Details\n9 for Exiting: ";
        cin>> input;
        switch (input){
            case 1:
                loading ();
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                c.available_cars (0);
                cout << endl << endl;
                system ("PAUSE");
                get_menu ();
                break;
            case 2:
                loading ();
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                c.new_car_addition ();
                get_menu ();

                break;
            case 3:
                if (c.isempty ()){
                    break;
                }
                loading ();
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                s.check_new_customer (0);
        
                s.renters ();
                system("PAUSE");
                get_menu ();
                break;
            case 4:
                if (c.isempty ()){
                    break;
                }
                loading ();
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                s.check_new_customer (0);
                s.buyers ();

                system ("PAUSE");
                get_menu ();

                break;
            case 5:
                if (c.isempty ()){
                    cout << "We are currently not accepting cars !" << endl;
                    break;
                }
                loading ();
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                customer_checker = s.check_new_customer (1);
                if (customer_checker == 1){
                    cout << "We have not made any deal yet !"<<endl;
                    system ("PAUSE");
                    break;
                }

                s.returners ();
                system ("PAUSE");
                get_menu ();

                break;
            case 6 :
                if (c.isempty ()){
                    cout << "We are currently not accepting cars !" << endl;
                    break;
                }

                loading ();
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                customer_checker = s.check_new_customer (1);
                if (customer_checker == 1){
                    cout << "We have not made any deal yet !"<<endl;
                    system ("PAUSE");
                    break;
                }

                s.sellers ();
                system ("PAUSE");
                get_menu ();
                break;
            case 7 : 
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                starter ();
                cout <<"\t\t\t\t\t|| Accounting Section || \n\n\n";
                cout <<"Current balance of the shop -- > "<<balance<<endl;
                if (profit >=0){
                    cout <<" Profit for the day is--> "<<profit <<" Rs "<< endl;
                }
                else {
                    cout <<"The loss for the day is -- > "<<-profit << " Rs" << endl<<endl;
                }

                system ("PAUSE");
                get_menu ();

                break;
            case 8:
                system ("cls");
                c.available_cars (0);

                cout << "Enter the model of the car: ";
                cin >> taker;
                system ("cls");
                cout << "\t\t || NOTE --> PLEASE USE '_' INSTEAD OF USING SPACE ||  \n\t\tPlEASE USE CAPITAL LETTERS WHENEVER NECESSARAY\n\n";
                c.car_details (taker);
                system ("PAUSE");
                get_menu ();
                break;

            case 9:
                exiting ();
                system ("cls");
                
                cout<<"\t\t\t\t\tPROGRAMMED AND MANAGED BY \n\n\n";
                cout<<"\t\t\t\t\t\t RAHUL RAWAT "<<endl;
                break;
            default : 
                cout << " Invalid Input ! "<<endl;
                break;
        }
    }
}
