#include <iostream>
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

using namespace clang;
using namespace std;
using namespace llvm;
using namespace clang::ast_matchers;

namespace MyPlugin {
    class MyHandler : public MatchFinder::MatchCallback {
    private:
        CompilerInstance &ci;
        
    public:
        MyHandler(CompilerInstance &ci) :ci(ci) {}
        
        void run(const MatchFinder::MatchResult &Result) {
            if (const ObjCInterfaceDecl *decl = Result.Nodes.getNodeAs<ObjCInterfaceDecl>("ObjCInterfaceDecl")) {
                size_t pos = decl->getName().find('_');
                if (pos != StringRef::npos) {
                    DiagnosticsEngine &D = ci.getDiagnostics();
                    SourceLocation loc = decl->getLocation().getLocWithOffset(pos);
                    D.Report(loc, D.getCustomDiagID(DiagnosticsEngine::Error, "iOS_Trick：类名中不能带有下划线"));
                }
                
                StringRef className = decl -> getName();
                char c = className[0];
                if (isLowercase(c)) {
                    std::string tempName = className;
                    tempName[0] = toUppercase(c);
                    StringRef replacement(tempName);
                    SourceLocation nameStart = decl->getLocation();
                    SourceLocation nameEnd = nameStart.getLocWithOffset(className.size() - 1);
                    FixItHint fixItHint = FixItHint::CreateReplacement(SourceRange(nameStart, nameEnd), replacement);
                    
                    DiagnosticsEngine &D = ci.getDiagnostics();
                    int diagID = D.getCustomDiagID(DiagnosticsEngine::Error, "iOS_Trick：类名不能以小写字母开头");
                    SourceLocation location = decl->getLocation();
                    D.Report(location, diagID).AddFixItHint(fixItHint);
                }
            }
        }
    };
    
    class MyASTConsumer: public ASTConsumer {
    private:
        MatchFinder matcher;
        MyHandler handler;
        
    public:
        MyASTConsumer(CompilerInstance &ci) :handler(ci) {
            matcher.addMatcher(objcInterfaceDecl().bind("ObjCInterfaceDecl"), &handler);
        }
        
        void HandleTranslationUnit(ASTContext &context) {
            matcher.matchAST(context);
        }
    };
    
    class MyASTAction: public PluginASTAction {
    public:
        unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &ci, StringRef iFile) {
            return unique_ptr<MyASTConsumer> (new MyASTConsumer(ci));
        }
        
        bool ParseArgs(const CompilerInstance &ci, const vector<string> &args) {
            return true;
        }
    };
}

static FrontendPluginRegistry::Add<MyPlugin::MyASTAction>
X("MyPlugin", "The MyPlugin is my first clang-plugin.");

