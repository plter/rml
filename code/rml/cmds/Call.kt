package rml.cmds

import rml.Arg
import rml.Scope

class Call(funcName: String, to: String?, parent: Scope?) : Command(parent) {
    private val _funcName: String = funcName
    val funcName: String get() = _funcName

    private val _args = ArrayList<Arg>()
    val args: ArrayList<Arg> get() = _args

    private val _to: String? = to

    fun addArg(arg: Arg) {
        _args.add(arg)
    }

    override fun execute(): Var? {
        val f = getFunc(funcName)
        if (f != null) {
            val result = f.execute(args)
            if (_to != null) {
                val toVar = getVar(_to)
                toVar?.value = result?.value
            }
        } else {
            println("Function $funcName not found")
        }
        return null
    }
}