package rml

import rml.cmds.Arg
import rml.cmds.Call
import rml.cmds.Return
import rml.cmds.Var
import rml.funcs.Func

class RMLReader(source: String?, fileId: String = "untitled") : XMLReader(source, fileId) {

    private val _app = Application(null)

    private var _currentScope: Context? = _app
    private var _currentCall: Call? = null

    override fun elementStart(tagName: String, attributes: Map<String, String>) {
        when (tagName) {
            "call" -> {
                _currentCall = Call(attributes["func"]!!, attributes["to"], attributes["target"], _currentScope, currentLineNum, fileId)
                (_currentScope as? Func)?.addCommand(_currentCall!!)
            }
            "arg" -> {
                _currentCall?.addArg(Arg(attributes["value"], attributes["ref"], _currentScope, currentLineNum, fileId))
            }
            "var" -> {
                (_currentScope as? Func)?.addCommand(Var(attributes["name"], attributes["value"], attributes["ref"], _currentScope, currentLineNum, fileId))
            }
            "return" -> {
                (_currentScope as? Func)?.addCommand(Return(attributes["ref"], _currentScope, currentLineNum, fileId))
            }
            "func" -> {
                val func = Func(attributes["name"], attributes["ns"], _currentScope)
                _currentScope?.addFunc(func)
                _currentScope = func
            }
        }
    }

    override fun elementEnd(tagName: String) {
        when (tagName) {
            "func" -> {
                _currentScope = _currentScope?.parent
            }
            "call" -> {
                _currentCall = null
            }
        }
    }

    override fun commentContent(content: String) {
    }

    fun run() {
        _app.run()
    }
}