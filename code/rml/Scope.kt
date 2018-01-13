package rml

open class Scope(parent: Scope?) {

    private val _parent: Scope? = parent
    val parent: Scope? get() = _parent

    private val _funcs = HashMap<String, Func>()
    val funcs: HashMap<String, Func> get() = _funcs

    private val _vars = HashMap<String, Var>()
    val vars: HashMap<String, Var> get() = _vars

    private var _calls = ArrayList<Call>()
    val calls: List<Call> get() = _calls


    fun addFunc(func: Func) {
        _funcs[func.fullyQualifiedName!!] = func
    }

    fun addVar(variable: Var) {
        _vars[variable.name!!] = variable
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

    fun getVar(name: String): Var? {
        val v = vars[name]
        if (v != null) {
            return v
        } else {
            if (parent != null) {
                return parent?.getVar(name)
            } else {
                return null
            }
        }
    }

    fun getRoot(): Scope? {
        if (parent != null) {
            return parent?.getRoot()
        } else {
            return this
        }
    }

    fun addCall(call: Call) {
        _calls.add(call)
    }
}