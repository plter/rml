package rml.funcs

import rml.Context
import rml.cmds.Arg
import rml.cmds.Command
import rml.cmds.Return
import rml.cmds.Var

class FuncState(name: String?, ns: String?, funcs: HashMap<String, Func>, parent: Context?) : Func(name, ns, parent) {

    private val _funcs = funcs
    private var _varsStatus = HashMap<String, Var>()


    fun getVar(name: String): Var? {
        val v = _varsStatus[name]
        if (v != null) {
            return v
        } else {
            if (parent != null) {
                return (parent as? FuncState)?.getVar(name)
            } else {
                return null
            }
        }
    }

    fun setVar(variable: Var?) {
        if (variable != null) {
            _varsStatus[variable.name!!] = variable
        }
    }

    override fun execute(args: List<Arg>): Var? {

        val arguments = CreateArray(this).execute(args)
        arguments?.name = "arguments"
        setVar(arguments)

        for (c in commands) {
            c.parent = this
            val result = c.execute()
            if (c is Var) {
                setVar(result)
            } else if (c is Return) {
                return result
            }
        }
        return null
    }
}