package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Var

class CreateArray(parent: Context?) : Func("CreateArray", null, parent) {

    override fun execute(args: List<Arg>): Var? {
        val arr = ArrayList<Any?>()
        args.mapTo(arr) { it.value }
        return Var(null, arr, null, parent, 0, "CreateArray.kt")
    }
}