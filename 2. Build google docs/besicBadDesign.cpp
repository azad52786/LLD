#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class DocumentEditor
{
private:
    vector<string> elements;
    string renderedDocument;

public:
    void addText(string text)
    {
        this->elements.push_back(text);
    }

    void addImage(string imagePath)
    {
        this->elements.push_back(imagePath);
    }

    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            string result;
            for (auto &element : elements)
            {
                // Here open close principle is voilated
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" || element.substr(element.size() - 4) == ".png"))
                {
                    result += "IMAGE: " + element + "\n";
                }
                else
                {
                    result += "TEXT: " + element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile()
    {
        ofstream file("document.txt");
        if (file.is_open())
        {
            file << renderDocument();
            file.close();
            cout << "Document saved to document.txt" << endl
                 << endl;
            renderedDocument = "";
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

int main()
{
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument() << endl;

    editor.saveToFile();

    editor.addImage("picture 1.jpg");
    editor.addText("This is a document editor 1.");

    cout << editor.renderDocument() << endl;
    editor.saveToFile();
    return 0;
}