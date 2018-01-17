package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Var

class Print(parent: Context?) : Func("print", null, parent) {

    override fun execute(args: List<Arg>): Var? {
        val sb = StringBuilder()
        for (a in args) {
            sb.append(a.value)
            sb.append(",")
        }

        print(sb.substring(0, sb.length - 1))
        return null
    }
}