#include <iostream>
#include <vector>

using namespace std;

struct Product {
    string name;
    int quantity;
    float price;
};

class Store {
    private:
        vector <Product> products;
        int nameLength     = 20;
        int quantityLength = 9;

    public:
        bool isOpen = true;

        // Constructor
        Store() {
            cout << "Hello!\nWelcome to the store managing program!" << "\n" << endl;
        }

        void displayMenu() {
            cout << "Main Menu\n" << endl;

            cout << "- menu:   Display the main menu" << endl;
            cout << "- show:   Show the list of all products" << endl;
            cout << "- add:    Add a product to the store" << endl;
            cout << "- edit:   Edit a product in the store" << endl;
            cout << "- cancel: Cancel any current task and go back to the main menu" << endl;
            cout << "- exit:   Quit this program" << endl;
            
            cout << endl;

            cout << "Please choose one of above options: " << endl;
        }

        string getUserCommand() {
            string userCommand;

            cin >> userCommand;
            cout << endl;
            return userCommand;
        }

        bool checkUserCommandCancel(string userCommand) {
            return (userCommand == "cancel");
        }

        void displayUserCancelledCommand() {
            cout << "\n Cancelled current action.\n Returning to main menu.\n" << endl;
        }

        void processUserMenuCommand() {
            string userMenuCommand = getUserCommand();

            if      (userMenuCommand == "menu")   displayMenu();
            else if (userMenuCommand == "show")   showProducts();
            else if (userMenuCommand == "add")    addProduct();
            else if (userMenuCommand == "edit")   editProduct();
            else if (userMenuCommand == "cancel") displayUserCancelledCommand();
            else if (userMenuCommand == "exit") {
                isOpen = false;
                cout << "Now closing the store management tool!\n\nSee you next time!" << endl;
            } else {
                cout << "Unknown command -" << userMenuCommand << "-.\nFalling back to main menu.\n" << endl;
                return;
            }
        }

        Product getNewProduct(string myName, int myQuantity, float myPrice) {
            struct Product myProduct;

            myProduct.name     = myName;
            myProduct.quantity = myQuantity;
            myProduct.price    = myPrice;

            return myProduct;
        }

        string getPrettyProductEntry(string myName, int length) {
            string myNamePretty = myName.substr(0, length);

            for (int i = 0; i < length; ++i) {
                if (!myNamePretty[i]) myNamePretty += " ";
            }

            return myNamePretty;
        }

        void displayProductToString(Product myProduct, int i) {
            string prettyName     = getPrettyProductEntry(myProduct.name, nameLength);
            string prettyQuantity = getPrettyProductEntry(to_string(myProduct.quantity), quantityLength);

            cout << "Id: " << i << "  || name: " << prettyName << ", quantity: " << prettyQuantity << ", price: " << myProduct.price << endl;;
        }

        void showProducts() {
            cout << "List of products:\n" << endl;
            
            for (int i = 0; i < products.size(); ++i) {
                displayProductToString(products[i], i);
            }
        }

        void addProduct() {
            string myName;
            int myQuantity;
            float myPrice;

            cout << "Input new product:\n";
            
            cout << "name: ";
            cin >> myName;

            cout << "quantity: ";
            cin >> myQuantity;

            cout << "price: ";
            cin >> myPrice;

            struct Product myProduct = getNewProduct(myName, myQuantity, myPrice);

            products.push_back(myProduct);
        }

        void displayProductSearched(int productId) {
            cout << "Result of product id " << productId << " search:\n" << endl;
            displayProductToString(products[productId], productId);
        }

        void displayInvalidSearched(int numSearched) {
            cout << "Invalid or unknown product id " << numSearched << " , returning to main menu.\n" << endl;
        }

        void processShowProduct() {
            cout << "Please input a product id to show among these:" << endl;
            showProducts();
            cout << endl;

            int productId;
            cin >> productId;

            if (!checkUserCommandCancel(to_string(productId))) {
                if (productId < products.size()) {
                    displayProductSearched(productId);
                    return;
                } else {
                    displayInvalidSearched(productId);
                    return;
                }
            } else {
                displayUserCancelledCommand();
                return;
            }
        }

        void displayPromptActionProduct(string typeOfChange) {
            cout << "To " << typeOfChange << " a product, please first type its product Id to access it, among these:" << endl;
            showProducts();
            cout << endl;
        }

        void displayChangedProduct(int productId) {
            cout << "Successfully changed product to:\n" << endl;
            displayProductToString(products[productId], productId);

            cout << "Returning to main menu\n" << endl;
        }

        void processChangeProductName() {
            displayPromptActionProduct("change the name of");
            int productId;
            cin >> productId;

            if (productId < products.size()) {
                displayProductSearched(productId);
                
                cout << "Current name is " << products[productId].name << ".\n" << endl;
                cout << "Please type a new name:" << endl;

                string productName;
                cin >> productName;

                if (!checkUserCommandCancel(productName)) {
                    products[productId].name = productName.substr(0, nameLength);
                    
                    displayChangedProduct(productId);
                    return;
                } else {
                    displayUserCancelledCommand();
                    return;
                }                
            } else {
                displayInvalidSearched(productId);
                return;
            }
        }

        void processChangeProductPrice() {
            displayPromptActionProduct("change the price of");
            int productId;
            cin >> productId;

            if (productId < products.size()) {
                displayProductSearched(productId);
                
                cout << "Current price is " << products[productId].price << ".\n" << endl;
                cout << "Please type a new price:" << endl;

                string str;
                cin >> str;

                if (!checkUserCommandCancel(str)) {
                    float productPrice = stof(str);

                    products[productId].price = productPrice;
                    
                    displayChangedProduct(productId);
                    return;
                } else {
                    displayUserCancelledCommand();
                    return;
                }                
            } else {
                displayInvalidSearched(productId);
                return;
            }
        }

        void processChangeProductQuantity() {
            displayPromptActionProduct("change the quantity of");
            int productId;
            cin >> productId;

            if (productId < products.size()) {
                displayProductSearched(productId);
                
                cout << "Current price is " << products[productId].price << ".\n" << endl;
                cout << "Please type a new price:" << endl;

                string str;
                cin >> str;

                if (!checkUserCommandCancel(str)) {
                    float productPrice = stof(str);

                    products[productId].price = productPrice;
                    
                    displayChangedProduct(productId);
                    return;
                } else {
                    displayUserCancelledCommand();
                    return;
                }                
            } else {
                displayInvalidSearched(productId);
                return;
            }
        }

        void processDeleteProduct() {
            cout << "You will now be prompted to type 2 Ids:" << endl;
            cout << "- First: the Id of the product you want to delete." << endl;
            cout << "- Second: if you don't want to delete any other product for now, type the same number.";
            cout << "\nElse, type the product Id of the last product you want to delete, and all inbetween products.";
            cout << "will be deleted too.\n\nYou can type cancel to return to main menu any time." << endl;

            displayPromptActionProduct("delete");
            int productId;
            cin >> productId;

            if (productId < products.size()) {
                cout << "Selected first product for delete (did not delete anything yet):" << endl;
                displayProductSearched(productId);

                cout << "Please input the id of the last product to delete:" << endl;
                string str_two;
                cin >> str_two;

                if (!checkUserCommandCancel(str_two)) {
                    // Easier for user to input the last deleting position (so we add a + 1)
                    int productIdTwo = stoi(str_two) + 1;

                    if (productId == productIdTwo) {
                        products.erase(products.begin() + productId);
                    } else {
                        products.erase(products.begin() + productId, products.begin() + productIdTwo);
                    }

                    showProducts();
                    return;
                }           
            } else {
                displayInvalidSearched(productId);
                return;
            }
        }

        void displayEditMenu() {
            cout << "Edit Menu\n" << endl;

            cout << "- showprod: Show a product's information" << endl;
            cout << "- name:     Change a product's name" << endl;
            cout << "- price:    Change a product's price" << endl;
            cout << "- quantity: Change a product's quantity" << endl;
            cout << "- delete:   Change a product's quantity" << endl;
            cout << "- cancel:   Cancel any current task and go back to the main menu" << endl;
            cout << "- exit:     Quit this program" << endl;
            
            cout << endl;

            cout << "Please choose one of above options: " << endl;
        }

        void processUserEditCommand() {
            string userEditCommand = getUserCommand();

            if      (userEditCommand == "showprod") processShowProduct();
            else if (userEditCommand == "name")     processChangeProductName();
            else if (userEditCommand == "price")    processChangeProductPrice();
            else if (userEditCommand == "quantity") processChangeProductQuantity();
            else if (userEditCommand == "delete")   processDeleteProduct();
            else if (userEditCommand == "cancel")   return;
            else if (userEditCommand == "exit") {
                isOpen = false;
                cout << "Now closing the store management tool!\n\nSee you next time!" << endl;
            } else {
                cout << "Unknown command -" << userEditCommand << "-.\nFalling back to edit menu.\n" << endl;
                return;
            }
        }

        void editProduct() {
            if (products.size() > 0) {
                displayEditMenu();
                processUserEditCommand();
            } else {
                cout << "Products list is currently empty, returning to main menu.\n" << endl;
            }
        }

        void exit() {
            isOpen = false;
        }

        void open() {
            isOpen = true;
        }
};

int main()
{
    Store myStore;

    while (myStore.isOpen) {
        myStore.displayMenu();
        myStore.processUserMenuCommand();
    }

    return 0;
}