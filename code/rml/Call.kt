package rml

class Call(funcName: String, parent: Scope?) : Scope(parent) {
    private val _funcName: String = funcName
    val funcName: String get() = _funcName

    private val _args = ArrayList<Arg>()
    val args: ArrayList<Arg> get() = _args

    fun addArg(arg: Arg) {
        _args.add(arg)
    }

    fun execute() {
        val f = getFunc(funcName)
        if (f != null) {
            f.execute(args)
        } else {
            println("Function $funcName not found")
        }
    }
}