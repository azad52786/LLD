#include <iostream>
#include <vector>
using namespace std;

class Product
{
private:
    string name;
    double price;

public:
    Product(string _name, double _price)
    {
        this->name = _name;
        this->price = _price;
    }

    double getPrice() const
    {
        return this->price;
    }

    void setPrice(double _price)
    {
        this->price = _price;
    }

    string getName() const
    {
        return this->name;
    }

    void setName(string _name)
    {
        this->name = _name;
    }
};

class ShoppingCart
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        this->products.push_back(p);
    }

    const vector<Product *> &getProducts() const
    {
        return this->products;
    }

    // task 1
    double calculateTotalPrice() const
    {
        double total = 0;
        for (auto &product : products)
        {
            total += product->getPrice();
        }

        return total;
    }

    // task 2
    void printInvoice() const
    {
        for (const auto &product : products)
        {
            cout << product->getName() << " Rs: " << product->getPrice() << endl;
        }

        cout << "Total: " << this->calculateTotalPrice() << endl;
    }

    // task 3
    void saveToDB()
    {
        cout << "Saving shopping cart to database..." << endl;
    }
};
//--------------------------------------------------------------------------------------------------
// All the three task handeled by ShoppingCart that is the voilation of SRP
//--------------------------------------------------------------------------------------------------

int main()
{
    ShoppingCart *cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));
    cart->printInvoice();
    cart->saveToDB();

    return 0;
}
