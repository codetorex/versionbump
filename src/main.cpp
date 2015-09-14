#include <iostream>
#include <string>
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>

#include "pathiterator.h"

using namespace rapidjson;
using namespace std;

class Operation {
public:
    virtual void Execute(Document &d, void *args) = 0;
};

class Increment : public Operation {
public:

    class Args {
    public:
        string value;
        int amount;
    };

    void Execute(Document &d, void *args) {
        Args *ia = (Args *) args;

    }
};

class OperationFactory {
public:
    static Operation *CreateCommand(string &name) {
        if (name == "increment") {
            return new Increment();
        }
    }
};

class Settings {
public:
    Document doc;

    void LoadFile(const char *path) {
        FILE *file = fopen(path, "r");
        char buffer[65536];
        FileReadStream is(file, buffer, sizeof(buffer));
        doc.ParseStream<0>(is);
        fclose(file);
    }


} g_State;



int main(int argc, char **argv) {
    //fstream f(argv[1], ios_base::in);

    PathIterator p("targets.versionbump.build");
    while (p.next()) {
        cout << p.get() << endl;
    }

    g_State.LoadFile(argv[1]);


    //d.Parse(json);

    Value &targets = g_State.doc["targets"];

    static const char *kTypeNames[] =
            {"Null", "False", "True", "Object", "Array", "String", "Number"};

    for (Value::ConstMemberIterator itr = targets.MemberBegin(); targets.MemberEnd() != itr; ++itr) {
        printf("Type of member %s is %s\n",
               itr->name.GetString(), kTypeNames[itr->value.GetType()]);
    }

    std::cout << "Hello world!" << "\n";
    return 0;
}