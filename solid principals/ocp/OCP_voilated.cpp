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

    double calculateTotalPrice() const
    {
        double total = 0;
        for (auto &product : products)
        {
            total += product->getPrice();
        }

        return total;
    }
};

class InvoicePrinter
{
private:
    ShoppingCart *sc;

public:
    InvoicePrinter(ShoppingCart *_sc)
    {
        this->sc = _sc;
    }

    void printInvoice() const
    {
        for (const auto &product : sc->getProducts())
        {
            cout << product->getName() << " Rs: " << product->getPrice() << endl;
        }

        cout << "Total: " << sc->calculateTotalPrice() << endl;
    }
};

class ShoppingCartStorage
{
private:
    ShoppingCart *sc;

public:
    ShoppingCartStorage(ShoppingCart *_sc)
    {
        this->sc = _sc;
    }

    void saveToSQLDatabase()
    {
        cout << "Saving shopping cart to SQL DB..." << endl;
    }

    void saveToMongoDatabase()
    {
        cout << "Saving shopping cart to Mongo DB..." << endl;
    }

    void saveToFile()
    {
        cout << "Saving shopping cart to File..." << endl;
    }
    
    // If another DB store method came we've to open this class and modify into it  this is a voilation of open close principal
};

int main()
{
    ShoppingCart *sc = new ShoppingCart();

    sc->addProduct(new Product("IPhone", 50000));
    sc->addProduct(new Product("MACBook", 55000));
    sc->addProduct(new Product("IPhone Charger", 5800));

    cout << "Total Price Of the Cart is: " << sc->calculateTotalPrice() << endl;

    InvoicePrinter *ip = new InvoicePrinter(sc);
    ip->printInvoice();

    ShoppingCartStorage *scs = new ShoppingCartStorage(sc);
    scs->saveToSQLDatabase();

    return 0;
}