package rml.funcs

import rml.cmds.Arg
import rml.Context
import rml.cmds.Command
import rml.cmds.Var

open class Func(name: String?, ns: String?, parent: Context?) : Context(parent) {

    private var _name: String? = name
    private var _ns: String? = ns

    val ns: String? get() = _ns
    val name: String? get() = _name

    private var _commands = ArrayList<Command>()
    val commands: List<Command> get() = _commands

    fun addCommand(cmd: Command) {
        _commands.add(cmd)
    }

    private var _fullyQualifiedName: String? = null
    val fullyQualifiedName: String?
        get() {
            if (_fullyQualifiedName == null) {
                val sb = StringBuilder()
                if (ns != null) {
                    sb.append(ns!!)
                    sb.append(".")
                }
                sb.append(name!!)
                _fullyQualifiedName = sb.toString()
            }
            return _fullyQualifiedName
        }

    private var _target: Var? = null
    var target: Var?
        get() = _target
        set(value) {
            _target = value
        }

    open fun execute(args: List<Arg>): Var? {
        val fs = FuncState(name, ns, funcs, this)
        var nc: Command?
        for (c in commands) {
            nc = c.clone()
            nc.parent = fs
            fs.addCommand(nc)
        }
        return fs.execute(args)
    }
}