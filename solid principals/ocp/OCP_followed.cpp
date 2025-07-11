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

// ShoppingCart has multiple (has-a relationship) Product
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

// InvoicePrinter has a (has-a relationship) ShoppingCart
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

// InvoicePrinter has a (has-a relationship) ShoppingCart
// Abstract Class
class DBPersistance
{
private:
    ShoppingCart *sc = new ShoppingCart();

public:
    virtual void save(ShoppingCart *sc) = 0; // Pure virtual function
};

class SQLDBPersistance : public DBPersistance
{
public:
    void save(ShoppingCart *sc) override
    {
        cout << "Saving shopping cart to SQL DB..." << endl;
    }
};

class MongoDBPersistance : public DBPersistance
{
public:
    void save(ShoppingCart *sc) override
    {
        cout << "Saving shopping cart to Mongo DB..." << endl;
    }
};

class FilePersistance : public DBPersistance
{
public:
    void save(ShoppingCart *sc) override
    {
        cout << "Saving shopping cart to File System..." << endl;
    }
};

int main()
{
    ShoppingCart *cart = new ShoppingCart();

    cart->addProduct(new Product("IPhone", 50000));
    cart->addProduct(new Product("MACBook", 55000));
    cart->addProduct(new Product("IPhone Charger", 5800));

    DBPersistance *sql = new SQLDBPersistance();
    DBPersistance *mongo = new MongoDBPersistance();
    DBPersistance *file = new FilePersistance();

    sql->save(cart);
    mongo->save(cart);
    file->save(cart);

    return 0;
}