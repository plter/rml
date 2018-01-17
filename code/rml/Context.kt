package rml

import rml.cmds.Command
import rml.cmds.Return
import rml.cmds.Var
import rml.funcs.Func

open class Context(parent: Context?) {

    private var _parent: Context? = parent
    var parent: Context?
        get() = _parent
        set(value) {
            _parent = value
        }

    private val _funcs = HashMap<String, Func>()
    val funcs: HashMap<String, Func> get() = _funcs


    fun addFunc(func: Func) {
        _funcs[func.fullyQualifiedName!!] = func
    }

    fun getFunc(fullyQualifiedName: String): Func? {
        val f = funcs[fullyQualifiedName]
        if (f != null) {
            return f
        } else {
            if (parent != null) {
                return parent?.getFunc(fullyQualifiedName)
            } else {
                return null
            }
        }
    }


    fun getRoot(): Context? {
        return if (parent != null) {
            parent?.getRoot()
        } else {
            this
        }
    }
}