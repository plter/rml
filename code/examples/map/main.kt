import rml.RMLReader

fun main(args: Array<String>) {

    val s = readFile("app.xml")
    val r = RMLReader(s, "app.xml")
    r.read()
    r.run()
}