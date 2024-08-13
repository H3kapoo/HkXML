#pragma once

#include <memory>
#include <vector>

namespace hk
{

/* DISCLAIMER:
    - very basic error checks and notifiers
    - ![CDATA[ not supported
    - < > ? / are allowed inside tag values
    - " character is not escaped inside tag values
    - <? processing information ?> not supported
    - Sure, it can be way more optimized but this wasn't the goal.
    - Except for a bit of back and forth, for all intents and purposes the algorithm is O(N)
      and the data is streamed directly from the file. Small adaptations can be done to read
      and process data from an in memory buffer.
    - Not intented to be used in any commercial product. Experimental only.
*/

class XMLDecoder
{
public:
    struct Node;
    using Tag = std::pair<std::string, std::string>;
    using NodeSPtr = std::shared_ptr<Node>;
    using NodeListPtr = std::vector<NodeSPtr>;
    using ErrorData = std::string;
    using AttrPairVec = std::vector<std::pair<std::string, std::string>>;
    using XmlResult = std::pair<NodeListPtr, ErrorData>;

    struct Node
    {
        void show(const uint32_t depth = 0);

        std::string nodeName;
        std::string innerText;
        AttrPairVec attributes;
        NodeListPtr children;
    };

    XMLDecoder() = default;

    XmlResult decodeFromStream(std::ifstream& stream);

    XmlResult decodeFromBuffer([[maybe_unused]] std::vector<uint8_t> buffer);

private:
    enum class State : uint8_t
    {
        Idle,
        AquireTagOpName,
        AquiredTagOpName,
        AquireTagClName,
        AquireAttribKey,
        AquiredAttribKey,
        AquireAttribValue,
        SkipComment,
    };

    XmlResult decode(std::ifstream& stream, const State startState = State::Idle);

    std::string getStateString(const State& state);

    void changeState(State& state, State newState);
};
} // namespace hk