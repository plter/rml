package rml.funcs

import rml.Scope
import rml.cmds.Var

open class Func(name: String?, ns: String?, parent: Scope?) : Scope(parent) {

    private var _name: String? = name
    private var _ns: String? = ns

    val ns: String? get() = _ns
    val name: String? get() = _name

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
}