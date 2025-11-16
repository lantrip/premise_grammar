import { $api } from "@/lib/api/client";
import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from "@/components/ui/table";
import { Badge } from "@/components/ui/badge";

export default function BeatsPage() {
  const { data, isLoading, error } = $api.useQuery("get", "/api/beats");
  if (isLoading) return <div>Loading…</div>;
  if (error) return <div>Error loading beats</div>;
  const beats = data ?? [];
  return (
    <div className="space-y-4">
      <h2 className="text-xl font-semibold">Beats ({beats.length})</h2>
      <Table>
        <TableHeader>
          <TableRow>
            <TableHead>Text</TableHead>
            <TableHead>Section</TableHead>
            <TableHead>File</TableHead>
            <TableHead>Entities</TableHead>
            <TableHead>Importance</TableHead>
          </TableRow>
        </TableHeader>
        <TableBody>
          {beats.map((b) => (
            <TableRow key={b.id}>
              <TableCell className="max-w-[480px] whitespace-pre-wrap">
                {b.text}
              </TableCell>
              <TableCell>{b.section?.scene ?? b.section?.act ?? ""}</TableCell>
              <TableCell className="text-xs text-muted-foreground">
                {b.file}
              </TableCell>
              <TableCell>
                <div className="flex flex-wrap gap-1">
                  {b.entities.map((e) => (
                    <Badge key={e} variant="secondary">
                      {e}
                    </Badge>
                  ))}
                </div>
              </TableCell>
              <TableCell>{b.importance?.score?.toFixed?.(2) ?? "—"}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </div>
  );
}



