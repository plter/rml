package rml.funcs

import rml.Context
import rml.cmds.Arg
import rml.cmds.Var

class Println(parent: Context?) : Func("println", null, parent) {

    override fun execute(args: List<Arg>): Var? {
        Print(parent).execute(args)
        println()
        return null
    }
}