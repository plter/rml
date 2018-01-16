package rml.funcs

import rml.Arg
import rml.Scope
import rml.cmds.Var

class CreateArray(parent: Scope?) : Func("CreateArray", null, parent) {

    override fun execute(args: List<Arg>): Var? {
        val arr = ArrayList<Any?>()
        args.mapTo(arr) { it.getValue() }
        return Var(null, arr, null, parent, 0, "CreateArray.kt")
    }
}