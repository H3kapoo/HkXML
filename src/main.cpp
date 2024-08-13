#include <fstream>

#include "Utility.hpp"
#include "hkXml.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printlne("Incorrect number of arguments: %d", argc);
        printlne("Usage %s <ims_path>", argv[0]);
        return 1;
    }

    std::ifstream xmlFile{argv[1]};

    if (xmlFile.fail())
    {
        printlne("Failed to find/open: %s", argv[1]);
        return 1;
    }

    hk::XMLDecoder::XmlResult nodes = hk::XMLDecoder().decodeFromStream(xmlFile);

    if (!nodes.second.empty())
    {
        printlne("ERROR: %s", nodes.second.c_str());
        return 1;
    }

    for (const hk::XMLDecoder::NodeSPtr& node : nodes.first)
    {
        node->show();
    }
}
