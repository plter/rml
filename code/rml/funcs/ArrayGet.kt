package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Var

class ArrayGet(parent: Context?) : Func("get", "array", parent) {
    override fun execute(args: List<Arg>): Var? {
        if (args.size == 2) {
            return Var(null, (args[1].value as List<*>)[(args[0].value as String).toInt()], null, parent, 0, "ArrayGet.kt")
        } else {
            error("array.get requires 1 arg")
        }
    }
}