package rml

class RMLReader(source: String?) : XMLReader(source) {

    private val _app = Application(null)

    private var _currentScope: Scope? = _app
    private var currentCall: Call? = null

    override fun elementStart(tagName: String, attributes: Map<String, String>) {
        when (tagName) {
            "call" -> {
                currentCall = Call(attributes["func"]!!, _currentScope)
                _currentScope?.addCall(currentCall!!)
            }
            "arg" -> {
                val arg = Arg(attributes["value"], attributes["ref"], _currentScope)
                currentCall?.addArg(arg)
            }
            "var" -> {
                val variable = Var(attributes["name"], attributes["value"], attributes["ref"], _currentScope)
                _currentScope?.addVar(variable)
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
        }
    }

    override fun commentContent(content: String) {
    }

    fun run() {
        _app.run()
    }
}