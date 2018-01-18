package rml.funcs

import rml.Context
import rml.cmds.Arg
import rml.cmds.Var


class FormString(parent: Context?) : Func("formString", null, parent) {
    override fun execute(args: List<Arg>): Var? {
        val sb = StringBuilder()
        for (a in args) {
            sb.append(a.value)
        }
        return Var(null, sb.toString(), null, this, 0, "FormString.kt")
    }
}