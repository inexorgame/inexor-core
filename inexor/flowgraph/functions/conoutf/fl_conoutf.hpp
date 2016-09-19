/// @file fl_conoutf.hpp
/// @author Johannes Schneider
/// @brief links the game engine's conoutf function to the 3D Visual Scripting Enviroment.

#ifndef INEXOR_VSCRIPT_CONOUTF_HEADER
#define INEXOR_VSCRIPT_CONOUTF_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace vscript {

    class CFunctionConoutfNode : public CScriptNode
    {
        protected:

            std::string console_text;

        public:

            CFunctionConoutfNode(const vec, const char*);
            ~CFunctionConoutfNode();
            
            void in();
            void set_text(const char* text);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif