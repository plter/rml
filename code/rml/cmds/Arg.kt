package rml.cmds

import rml.Context

class Arg(value: Any?, refName: String?, parent: Context?, lineNum: Int, fileId: String) : Var(null, value, refName, parent, lineNum, fileId) {


    override fun clone(): Arg {
        return Arg(value, refName, parent, lineNum, fileId)
    }

    override fun toString(): String {
        return "Arg($value)"
    }

}