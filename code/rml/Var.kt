package rml

class Var(name: String?, value: String?, parent: Scope?) : Scope(parent) {

    private var _name: String? = name
    private var _value: String? = value

    val name: String?
        get() = _name

    val value: String?
        get() = _value
}