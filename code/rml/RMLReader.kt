package rml

import rml.cmds.Call
import rml.cmds.Return
import rml.cmds.Var

class RMLReader(source: String?) : XMLReader(source) {

    private val _app = Application(null)

    private var _currentScope: Scope? = _app
    private var _currentCall: Call? = null

    override fun elementStart(tagName: String, attributes: Map<String, String>) {
        when (tagName) {
            "call" -> {
                _currentCall = Call(attributes["func"]!!, attributes["to"], _currentScope)
                _currentScope?.addCommand(_currentCall!!)
            }
            "arg" -> {
                _currentCall?.addArg(Arg(attributes["value"], attributes["ref"], _currentScope))
            }
            "var" -> {
                _currentScope?.addCommand(Var(attributes["name"], attributes["value"], attributes["ref"], _currentScope))
            }
            "return" -> {
                _currentScope?.addCommand(Return(attributes["ref"], _currentScope))
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