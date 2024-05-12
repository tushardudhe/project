<?php
if (!isset($_COOKIE['username'])) {
    header("location:index.php");
} else {
    $name = "Administrator";
}
require_once("config.php");
?>
<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title><?php include("title.php"); ?></title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.10.5/font/bootstrap-icons.css">
</head>
<body>
<?php include("navbar.php");?>
    <div class="container py-3">
        <p class="display-6 border-bottom">Power Consumption Timeline</p>
        <?php if (isset($_COOKIE['status'])) {
        ?>
            <div class="alert alert-success alert-dismissible fade show" role="alert">
                <strong>Deleted!</strong>
                <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
            </div>
        <?php
        }
        ?>
        <table class="table table-hover table-striped">
            <thead>
                <tr>
                    <th scope="col">#</th>
                    <th scope="col">Voltage(volts)</th>
                    <th scope="col">Current(Amps)</th>
                    <th scope="col">Power(Watts)</th>
                    <th scope="col">Time</th>
                    <th scope="col">Date</th>
                    <th scope="col">Delete</th>
                </tr>
            </thead>
            <tbody>
                <?php
                $sql = mysqli_query($al, "SELECT * FROM data ORDER BY id DESC LIMIT 0,10");
                $x = 1;
                while ($pr = mysqli_fetch_assoc($sql)) { ?>
                    <tr>
                        <th scope="row"><?php echo $x++; ?></th>
                        <td><?php echo $pr['voltage']; ?></td>
                        <td><?php echo $pr['current']; ?></td>
                        <td><?php echo $pr['voltage'] * $pr['current']; ?></td>
                        <td><?php echo $pr['time']; ?></td>
                        <td><?php echo $pr['date']; ?></td>
                        <td><a href="delete.php?key=<?php echo $pr['veganhash']; ?>" class="btn btn-danger btn-sm">Delete</a></td>
                    </tr>
                <?php } ?>
                <tr>
                    <td colspan="7"><a href="view-all.php" class="btn btn-success">View All Records</a> </td>
                </tr>
            </tbody>
        </table>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ENjdO4Dr2bkBIFxQpeoTz1HIcje39Wm4jDKdf19U8gI4ddQ3GYNS7NTKfAdVQSZe" crossorigin="anonymous"></script>
</body>

</html>