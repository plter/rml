package rml

class Call(funcName: String, parent: Scope?) : Command(parent) {
    private val _funcName: String = funcName
    val funcName: String get() = _funcName

    private val _args = ArrayList<Arg>()
    val args: ArrayList<Arg> get() = _args

    fun addArg(arg: Arg) {
        _args.add(arg)
    }

    override fun execute(): Var? {
        val f = getFunc(funcName)
        if (f != null) {
            f.execute(args)
        } else {
            println("Function $funcName not found")
        }
        return null
    }
}