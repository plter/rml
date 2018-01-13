import kotlinx.cinterop.ByteVar
import kotlinx.cinterop.allocArray
import kotlinx.cinterop.memScoped
import kotlinx.cinterop.toKString
import platform.posix.*


fun readFile(file: String): String? {
    var content: String? = null
    memScoped {
        val fp = fopen(file, "r") ?: error("File not found $file")
        fseek(fp, 0, SEEK_END)
        val fileSize = ftell(fp)
        fseek(fp, 0, SEEK_SET)
        val buf = allocArray<ByteVar>(fileSize)
        fread(buf, 1, fileSize, fp)
        content = buf.toKString()
        fclose(fp)
    }
    return content
}