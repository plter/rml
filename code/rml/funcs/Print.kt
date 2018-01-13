package rml.funcs

import rml.Arg
import rml.Func
import rml.Scope

class Print(parent: Scope?) : Func("print", null, parent) {

    override fun execute(args: List<Arg>) {
        val sb = StringBuilder()
        for (a in args) {
            sb.append(a.getValue())
            sb.append(",")
        }
        print(sb.substring(0, sb.length - 1))
    }
}